#!/usr/bin/python3
import sys

ERR_MSG = "Usage: {} pid search write".format(sys.argv[0])


def p_sline(addr, perm, offset, device, inode, pathname):
    """Prints contents of sline"""
    print("\taddresses = {}".format(addr))
    print("\tpermisions = {}".format(perm))
    print("\toffset = {}".format(offset))
    print("\tdevice = {}".format(device))
    print("\tinode = {}".format(inode))
    print("\tpathname = {}".format(pathname))


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print(ERR_MSG)
        sys.exit(1)
    try:
        pid = int(sys.argv[1])
    except ValueError as e:
        print(e, "\npid should be an integer greater than 0")
        sys.exit(1)
    search_str = sys.argv[2]
    write_str = sys.argv[3]
    if pid <= 0 or search_str == '' or write_str == '':
        print(ERR_MSG)
        sys.exit(1)

    mem_filename = "/proc/{}/mem".format(pid)
    try:
        maps_file = open("/proc/{}/maps".format(pid), 'r')
    except IOError as e:
        print(e)
        sys.exit(1)

    for line in maps_file:
        sline = line.split(' ')
        if sline[-1][:-1] != "[heap]":
            continue
        print("Found [heap]:")
        addr = sline[0]
        perm = sline[1]
        offset = sline[2]
        device = sline[3]
        inode = sline[4]
        pathname = sline[-1][:-1]
        p_sline(addr, perm, offset, device, inode, pathname)
        if perm[0] != 'r' or perm[1] != 'w':
            print("{} does not have read/write permission".format(pathname))
            maps_file.close()
            sys.exit(1)

        addr = addr.split("-")
        if len(addr) != 2:
            print("Wrong addr format")
            maps_file.close()
            sys.exit(1)
        try:
            addr_start = int(addr[0], 16)
            addr_end = int(addr[1], 16)
        except ValueError as e:
            print(e, "unable to convert addr to integer")

        try:
            mem_file = open(mem_filename, 'rb+')
        except IOError as e:
            print(e)
            maps_file.close()
            sys.exit(1)

        mem_file.seek(addr_start)
        heap = mem_file.read(addr_end - addr_start)
        try:
            i = heap.index(bytes(search_str, "ASCII"))
        except Exception:
            print("Can't find '{}'".format(search_str))
            maps_file.close()
            mem_file.close()
            sys.exit(1)

        print("Found '{}' at {:x}".format(search_str, i))
        print("Writing '{}' at {:x}".format(write_str, addr_start + i))
        mem_file.seek(addr_start + i)
        mem_file.write(bytes(write_str, "ASCII"))
        maps_file.close()
        mem_file.close()
        break
