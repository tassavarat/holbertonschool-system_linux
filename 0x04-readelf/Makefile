CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
0 = $(patsubst %.c, %.o, $(wildcard 0-*.c))
1 = $(patsubst %.c, %.o, $(wildcard 1-*.c))
2 = $(patsubst %.c, %.o, $(wildcard 2-*.c))
100 = $(patsubst %.c, %.o, $(wildcard 100-*.c))

.PHONY: all clean

0-hreadelf: $(0)
	$(CC) $(CFLAGS) $(0) -o 0-hreadelf

1-hreadelf: $(1)
	$(CC) $(CFLAGS) $(1) -o 1-hreadelf

2-hreadelf: $(2)
	$(CC) $(CFLAGS) $(2) -o 2-hreadelf

100-hreadelf: $(100)
	$(CC) $(CFLAGS) $(100) -o 100-hreadelf

clean:
	rm -f $(OBJS) 0-hreadelf
