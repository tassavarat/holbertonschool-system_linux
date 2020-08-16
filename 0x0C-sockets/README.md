# 0x0C. Sockets

## Learning Objectives
* What is a socket and how it is represented on a Linux/UNIX system
* What are the different types of sockets
* What are the different socket domains
* How to create a socket
* How to bind a socket to an address/port
* How to listen and accept incoming traffic
* How to connect to a remote application
* What is the the HTTP protocol
* How to create a simple HTTP server

## Requirements
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project, is mandatory
* Your code should use the Betty style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
* You are not allowed to have more than 5 functions per file
* All your header files should be include guarded
* Unless specified otherwise, you are allowed to use the C standard library

## REST API
The goal of this project is to build a simple HTTP REST API in C.

This is going to be a really simple API, allowing us to manage a list of things to do (a.k.a a TODO list). Our database will be the RAM, meaning we won’t have any persistent storage. It’s not the purpose of this project anyway. Every time you start your server, the list of todos is empty.

A `todo` contains at least the following fields:

* `id` -> Positive integer, starting from `0`
* `title` -> String
* `description` -> String

 Here are the different routes that will have to be implemented:

* `/todos`
	* `POST` -> Creates a new todo
	* `GET` -> Retrieve all the todos
* `/todos?id={id}` (where `{id}` is a positive integer)
	* `GET` -> Retrieve the todo with the corresponding `id`
	* `DELETE` -> Delete the todo with the corresponding `id`

### [0. Listen](./0-server.c)
Write a program that opens an `IPv4/TCP` socket, and listens to traffic on port `12345` (Any address).

* Your program must hang indefinitely (It’ll eventually be killed by a signal during correction)
* You don’t have to accept entering connections
* Your program’s output won’t be checked, you can output any information you like

In a terminal:
```
alex@~/0x0C-sockets$ gcc -Wall -Wextra -Werror -pedantic -o 0-server 0-server.c 
alex@~/0x0C-sockets$ ./0-server 
Server listening on port 12345
```

In a second terminal:
```
alex@~/0x0C-sockets$ lsof -i :12345
COMMAND    PID    USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
0-server 24895 vagrant    3u  IPv4 251230      0t0  TCP *:12345 (LISTEN)
alex@~/0x0C-sockets$ killall 0-server
alex@~/0x0C-sockets$
```
