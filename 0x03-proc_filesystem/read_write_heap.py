#!/usr/bin/python3
import sys


def mem():
    """Overwrites search_str with contents of write_str"""
    try:
        with open("/proc/{}/mem".format(pid), 'rb+') as mem_file:
            mem_file.seek(addr_start)
            heap = mem_file.read(addr_end - addr_start)
            try:
                # i = heap.index(bytes(search_str + '\0', "ASCII"))
                i = heap.index(bytes(search_str, "ASCII"))
            except Exception as e:
                print(e)
                sys.exit(1)
            print("Found '{}' at {:x}".format(search_str, i))
            print("Writing '{}' at {:x}".format(write_str, addr_start + i))
            mem_file.seek(addr_start + i)
            mem_file.write(bytes(write_str + '\0', "ASCII"))
    except Exception as e:
        print(e)
        sys.exit(1)


def parse_line(line):
    """Parses through heap information

    Args:
        line: contains heap information

    Returns:
        addr_start and addr_end for heap
    """
    sline = line.split(' ')
    addr = sline[0]
    perm = sline[1]
    offset = sline[2]
    device = sline[3]
    inode = sline[4]
    print("Found [heap]:")
    print("\taddresses = {}".format(addr))
    print("\tpermisions = {}".format(perm))
    print("\toffset = {}".format(offset))
    print("\tdevice = {}".format(device))
    print("\tinode = {}".format(inode))
    if perm[0] != 'r' or perm[1] != 'w':
        print("{} does not have read/write permission".format(pathname))
        sys.exit(1)
    addr = addr.split('-')
    if len(addr) != 2:
        print("Wrong addr format")
        sys.exit(1)
    try:
        addr_start = int(addr[0], 16)
        addr_end = int(addr[1], 16)
    except Exception as e:
        print(e)
        sys.exit(1)
    print("\tAddr start [{:x}] | end [{:x}]".format(addr_start, addr_end))
    return addr_start, addr_end


def maps():
    """Opens specified maps file

    Returns:
        start and end addresses of heap
    """
    try:
        with open("/proc/{}/maps".format(pid), 'r') as maps_file:
            for line in maps_file:
                if line.endswith("[heap]\n"):
                    break
            return parse_line(line)
    except Exception as e:
        print(e)
        sys.exit(1)


def parse_argv():
    """Parses through argv while checking for usage error

    Returns:
        pid, search_str, write_str
    """
    err_msg = "Usage: {} pid search write".format(sys.argv[0])
    if len(sys.argv) != 4:
        print(err_msg)
        sys.exit(1)
    try:
        pid = int(sys.argv[1])
    except Exception as e:
        print(e)
        sys.exit(1)
    search_str = sys.argv[2]
    write_str = sys.argv[3]
    if pid < 1:  # or search_str == '' or write_str == '':
        print(err_msg)
        sys.exit(1)
    if len(sys.argv[2]) < len(sys.argv[3]):
        print("write_str longer than search_str")
        sys.exit(1)
    return pid, search_str, write_str


if __name__ == "__main__":
    pid, search_str, write_str = parse_argv()
    addr_start, addr_end = maps()
    mem()
