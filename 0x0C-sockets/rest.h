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
#define CONSTLEN		35

#define GET			"GET"
#define POST			"POST"
#define PATH			"/todos "
#define CONTLEN			"Content-Length: %lu\r\n"
#define RESP_OK			"HTTP/1.1 200 OK\r\n\r\n"
#define RESP_CREATED		"HTTP/1.1 201 Created\r\n"
#define RESP_NOTFOUND		"HTTP/1.1 404 Not Found\r\n\r\n"
#define RESP_LENREQ		"HTTP/1.1 Length Required\r\n\r\n"
#define RESP_UNPROCESSENT	"HTTP/1.1 422 Unprocessable Entity\r\n\r\n"

#define GET_LEN			strlen(GET)
#define POST_LEN		strlen(POST)
#define RESP_OK_LEN		strlen(RESP_OK)
#define RESP_NOTFOUND_LEN	strlen(RESP_NOTFOUND)
#define RESP_LENREQ_LEN		strlen(RESP_LENREQ)
#define RESP_UNPROCESSENT_LEN	strlen(RESP_UNPROCESSENT)

/**
 * struct todo_list_s - todo linked list
 * @id: member id
 * @title: title string
 * @desc: description string
 * @next: pointer to next todo node
 */
typedef struct todo_list_s
{
	size_t id;
	char *title;
	char *desc;
	struct todo_list_s *next;
} todo_list_t;

/**
 * struct todo_info_s - queue for todo linked list
 * @head: pointer to head todo node
 * @tail: pointer to tail todo node
 */
typedef struct todo_info_s
{
	struct todo_list_s *head;
	struct todo_list_s *tail;
} todo_info_t;

/* sockets.c */
int init_socket(void);
int accept_recv(int serv_fd, char *buffer);
int parse_error(char *buffer, int client_fd);

#endif /* REST_H */
