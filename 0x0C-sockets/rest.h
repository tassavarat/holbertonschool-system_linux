#ifndef REST_H
#define REST_H

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT			8080
#define BACKLOG			10

#define PATH			"/todos"
#define POST			"POST"

#define	CODE_201		"201 Created"
#define CODE_404		"404 Not Found"
#define CODE_422		"422 Unprocessable Entity"

#define RESP_OK			"HTTP/1.1 200 OK\r\n\r\n"
#define RESP_CREATED		"HTTP/1.1 201 Created\r\n"
#define RESP_NOTFOUND		"HTTP/1.1 404 Not Found\r\n\r\n"
#define RESP_UNPROCESSENT	"HTTP/1.1 422 Unprocessable Entity\r\n\r\n"

#define POST_LEN		strlen(POST)
#define RESP_OK_LEN		strlen(RESP_OK)
#define RESP_NOTFOUND_LEN	strlen(RESP_NOTFOUND)
#define RESP_UNPROCESSENT_LEN	strlen(RESP_UNPROCESSENT)

/**
 * struct todo - todo linked list
 * @id: member id
 * @title: title string
 * @desc: description string
 * @next: pointer to next todo node
 */
struct todo
{
	size_t id;
	char *title;
	char *desc;
	struct todo *next;
};

/**
 * struct client_info - client information
 * @fd: client file descriptor
 * @addr: client address
 */
struct client_info
{
	int fd;
	char *addr;
};

/* sockets.c */
int init_socket(void);
/* int accept_recv(int serv_fd, char *buffer); */
struct client_info *accept_recv(int serv_fd, char *buffer,
		struct client_info *client);

#endif /* REST_H */
