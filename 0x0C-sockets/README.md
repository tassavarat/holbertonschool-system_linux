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

### [1. Accept](./1-server.c)
Write a program that opens an `IPv4/TCP` socket, and listens to traffic on port `12345` (Any address).

Your program must accept an entering connection, print the IP address of the connected client, and close the connection right after
Output: See example below
In order to test your server, you can use the program `1-client` available on [this GitHub](https://github.com/holbertonschool/Sockets.c)

In a terminal:
```
alex@~/0x0C-sockets$ gcc -Wall -Wextra -Werror -pedantic -o 1-server 1-server.c 
alex@~/0x0C-sockets$ ./1-server 
Server listening on port 12345
Client connected: 127.0.0.1
alex@~/0x0C-sockets$
```
In a second terminal:
```
alex@~/0x0C-sockets$ ./1-client localhost 12345
Connected to localhost:12345
alex@~/0x0C-sockets$
```

### [2. Client](./2-client.c)
Write a program that connects to a listening server

Usage: `2-client <host> <port>`
Where `port` is an unsigned short
If the number of command-line arguments is not sufficient, yout program must display: `Usage: %s <host> <port>` (where `%s` must be replaced by the name of the program), followed by a new line and exit with `EXIT_FAILURE`
You can assume that `<port>` will be a positive integer
Once your client established a connection with the server, it must print a message, and exit successfully
In order to test your server, you can use the program `2-server` available on [this GitHub](https://github.com/holbertonschool/Sockets.c)

In a terminal:
```
alex@~/0x0C-sockets$ ./2-server 
Server listening on port 12345
Client connected: 127.0.0.1
```

In a second terminal:
```
alex@~/0x0C-sockets$ gcc -Wall -Wextra -Werror -pedantic -o 2-client 2-client.c 
alex@~/0x0C-sockets$ ./2-client localhost 12345
Connected to localhost:12345
alex@~/0x0C-sockets$
```

### [3. Roger](./3-server.c)
Write a program that opens an `IPv4/TCP` socket, and listens to traffic on port `12345` (Any address).

* Your program must:
	* Accept an entering connection
	* Print the IP address of the connected client
	* Wait for an incoming message from the connected client
	* Print the received message
	* Close the connection with the client
	* Exit
* Output: See example below
* In order to test your server, you can use the program `3-client` available on [this GitHub](https://github.com/holbertonschool/Sockets.c)

In a terminal:
```
alex@~/0x0C-sockets$ gcc -Wall -Wextra -Werror -pedantic -o 3-server 3-server.c 
alex@~/0x0C-sockets$ ./3-server 
Server listening on port 12345
Client connected: 127.0.0.1
Message received: "Holberton School !!!"
alex@~/0x0C-sockets$
```
In a second terminal:
```
alex@~/0x0C-sockets$ ./3-client localhost 12345 'Holberton School !!!'
Connected to localhost:12345
Sending the message: "Holberton School !!!"
Sent
alex@~/0x0C-sockets$
```

### [4. REST API - The Request](./Makefile)
Write a program that opens an `IPv4/TCP` socket, and listens to traffic on port `8080` (Any address).

* Your program must:
	* Accept an entering connection
	* Print the IP address of the connected client
	* Wait for an incoming message from the connected client
	* Print the full received HTTP request
	* Print the break-down of the first line of the received HTTP request (See example)
	* Send back a response to the connected client (HTTP 200 OK)
	* Close the connection with the client
	* Wait for the next connection
* The client will send an HTTP/1.1 request. You can find the `RFC` describing the HTTP protocol version `1.1` [here](https://intranet.hbtn.io/rltoken/lKmhLE_RqNgR9Ejw54mLVA).
* RFC’s are long and dense documents, but they are organized in a way that you can easily find what you are looking for :) (Tip: Sections 4, 5, 6 and 10)
* You can assume that the requests sent to your server will always be valid HTTP/1.1 requests, no trick.

Your `Makefile` must define the rule `todo_api_0`, which compiles and link your sources to form an executable with the same name.

In a terminal:
```
alex@~/0x0C-sockets$ make todo_api_0
[...]
alex@~/0x0C-sockets$ ./todo_api_0 
Server listening on port 8080
Client connected: 127.0.0.1
Raw request: "GET /test HTTP/1.1
User-Agent: curl/7.35.0
Host: localhost:8080
Accept: */*

"
Method: GET
Path: /test
Version: HTTP/1.1
Client connected: 127.0.0.1
Raw request: "POST /holberton HTTP/1.1
User-Agent: curl/7.35.0
Host: localhost:8080
Accept: */*

"
Method: POST
Path: /holberton
Version: HTTP/1.1
^C
alex@~/0x0C-sockets$
```
In a second terminal:
```
alex@~/0x0C-sockets$ curl -D - 'http://localhost:8080/test' 2> /dev/null | cat -e
HTTP/1.1 200 OK^M$
^M$
alex@~/0x0C-sockets$ curl -D - -X POST 'http://localhost:8080/holberton' 2> /dev/null | cat -e
HTTP/1.1 200 OK^M$
^M$
alex@~/0x0C-sockets$
```
