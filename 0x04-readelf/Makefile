CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
0 = $(patsubst %.c, %.o, $(wildcard 0-*.c))

.PHONY: all clean

0-hreadelf: $(0)
	$(CC) $(CFLAGS) $(0) -o 0-hreadelf

clean:
	rm -f $(OBJS) 0-hreadelf
