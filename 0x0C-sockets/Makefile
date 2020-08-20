CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g3

SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
0 = $(patsubst %.c, %.o, $(wildcard todo_api_0.c)) sockets.c
1 = $(patsubst %.c, %.o, $(wildcard todo_api_1.c)) sockets.c
2 = $(patsubst %.c, %.o, $(wildcard todo_api_2.c)) sockets.c
3 = $(patsubst %.c, %.o, $(wildcard todo_api_3.c)) sockets.c
4 = $(patsubst %.c, %.o, $(wildcard todo_api_4.c)) sockets.c response.c
5 = $(patsubst %.c, %.o, $(wildcard todo_api_5.c)) sockets.c response.c
6 = $(patsubst %.c, %.o, $(wildcard todo_api_6.c)) sockets.c response.c
7 = $(patsubst %.c, %.o, $(wildcard todo_api_7.c)) sockets.c response.c

.PHONY: todo_api_0 todo_api_1 todo_api_2 todo_api_3 todo_api_4 todo_api_5 todo_api_6 todo_api_7 clean

todo_api_0: $(0)
	$(CC) $(CFLAGS) $(0) -o todo_api_0

todo_api_1: $(1)
	$(CC) $(CFLAGS) $(1) -o todo_api_1

todo_api_2: $(2)
	$(CC) $(CFLAGS) $(2) -o todo_api_2

todo_api_3: $(3)
	$(CC) $(CFLAGS) $(3) -o todo_api_3

todo_api_4: $(4)
	$(CC) $(CFLAGS) $(4) -o todo_api_4

todo_api_5: $(5)
	$(CC) $(CFLAGS) $(5) -o todo_api_5

todo_api_6: $(6)
	$(CC) $(CFLAGS) $(6) -o todo_api_6

todo_api_7: $(7)
	$(CC) $(CFLAGS) $(7) -o todo_api_7

clean:
	rm -f $(OBJS) todo_api_0 todo_api_1 todo_api_2 todo_api_3 todo_api_4 todo_api_5 todo_api_6 todo_api_7
