#!/usr/bin/python3
import sys


def mem(mem_filename, addr_start, addr_end):
    """Opens specified mem file

    Args:
        mem_filename: name of mem file
        addr_start: address to start searching from
        addr_end: address to stop searching at
    """
    try:
        with open(mem_filename, 'rb+') as mem_file:
            mem_file.seek(addr_start)
            heap = mem_file.read(addr_end - addr_start)
            try:
                i = heap.index(bytes(search_str + '\0', "ASCII"))
            except Exception:
                print("Can't find '{}'".format(search_str))
                sys.exit(1)
            print("Found '{}' at {:x}".format(search_str, i))
            print("Writing '{}' at {:x}".format(write_str, addr_start + i))
            mem_file.seek(addr_start + i)
            mem_file.write(bytes(write_str + '\0', "ASCII"))
    except Exception as e:
        print(e)
        sys.exit(1)


def print_sline(addr, perm, offset, device, inode, pathname):
    """Prints contents of sline"""
    print("\taddresses = {}".format(addr))
    print("\tpermisions = {}".format(perm))
    print("\toffset = {}".format(offset))
    print("\tdevice = {}".format(device))
    print("\tinode = {}".format(inode))
    print("\tpathname = {}".format(pathname))


def parse_sline(sline):
    """Parses through sline

    Args:
        sline: line from maps to parse

    Returns:
        addr, perm, offset, device, inode, pathname
    """
    addr = sline[0]
    perm = sline[1]
    offset = sline[2]
    device = sline[3]
    inode = sline[4]
    pathname = sline[-1][:-1]
    return addr, perm, offset, device, inode, pathname


def maps():
    """Opens specified maps file

    Returns:
        mem_filename, addr_start, addr_end if successful
    """
    mem_filename = "/proc/{}/mem".format(pid)
    try:
        with open("/proc/{}/maps".format(pid), 'r') as maps_file:
            for line in maps_file:
                sline = line.split(' ')
                if sline[-1][:-1] != "[heap]":
                    continue
                print("Found [heap]:")
                addr, perm, offset, device, inode, pathname = \
                    parse_sline(sline)
                print_sline(addr, perm, offset, device, inode, pathname)
                if perm[0] != 'r' or perm[1] != 'w':
                    print("{} does not have \
                          read/write permission".format(pathname))
                    sys.exit(1)
                addr = addr.split("-")
                addr_start = int(addr[0], 16)
                addr_end = int(addr[1], 16)
                break
    except Exception as e:
        print(e)
        sys.exit(1)
    return mem_filename, addr_start, addr_end


def parse_argv():
    """Parses through argv

    Returns:
        pid, search_str, write_str if successful
    """
    ERR_MSG = "Usage: {} pid search write".format(sys.argv[0])
    if len(sys.argv) != 4:
        print(ERR_MSG)
        sys.exit(1)
    pid = int(sys.argv[1])
    search_str = sys.argv[2]
    write_str = sys.argv[3]
    if pid <= 0 or search_str == '' or write_str == '':
        print(ERR_MSG)
        sys.exit(1)
    if len(sys.argv[2]) < len(sys.argv[3]):
        print("write_str longer than search_str")
        sys.exit(1)
    return pid, search_str, write_str


if __name__ == "__main__":
    pid, search_str, write_str = parse_argv()
    mem_filename, addr_start, addr_end = maps()
    mem(mem_filename, addr_start, addr_end)
