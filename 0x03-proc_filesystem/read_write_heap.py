#!/usr/bin/python3
import sys


def error():
    print("Usage: {} pid search write".format(sys.argv[0]))
    sys.exit(1)


if len(sys.argv) != 4:
    error()
pid = int(sys.argv[1])
if pid <= 0:
    error()
search_str = sys.argv[2]
if search_str == '':
    error()
write_str = sys.argv[3]
if write_str == '':
    error()

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
    break
