CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g3

SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
0 = $(patsubst %.c, %.o, $(wildcard todo_api_0.c)) sockets.c

.PHONY: todo_api_0 clean

todo_api_0: $(0)
	$(CC) $(CFLAGS) $(0) -o todo_api_0

clean:
	rm -f $(OBJS)
