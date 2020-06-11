CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g3

SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
LIBS = $(patsubst %.c, %.o, shared.c)
0 = $(patsubst %.c, %.o, $(wildcard 0-*.c)) $(LIBS)
1 = $(patsubst %.c, %.o, $(wildcard 1-*.c)) $(LIBS)
2 = $(patsubst %.c, %.o, $(wildcard 2-*.c)) $(LIBS)
3 = $(patsubst %.c, %.o, $(wildcard 3-*.c)) $(LIBS)

.PHONY: strace_0 strace_1 strace_2 strace_3 clean

strace_0: $(0)
	$(CC) $(CFLAGS) $(0) -o strace_0

strace_1: $(1)
	$(CC) $(CFLAGS) $(1) -o strace_1

strace_2: $(2)
	$(CC) $(CFLAGS) $(2) -o strace_2

strace_3: $(3)
	$(CC) $(CFLAGS) $(3) -o strace_3

clean:
	rm -f $(OBJS) strace_*
