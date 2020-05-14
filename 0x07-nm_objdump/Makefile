CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
0 = $(patsubst %.c, %.o, hnm.c elf.c)

.PHONY: hnm clean

hnm: $(0)
	$(CC) $(CFLAGS) $(0) -o hnm
clean:
	rm -f $(OBJS) hnm
