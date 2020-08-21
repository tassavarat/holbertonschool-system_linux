#ifndef REST_H
#define REST_H

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define GETALL			-2
#define VERBOSE_OFF		0
#define VERBOSE_ON		1

#define PORT			8080
#define BACKLOG			10

#define POST_CONSTLEN		35
#define GET_CONSTLEN		2

#define POST			"POST"
#define GET			"GET"
#define DELETE			"DELETE"
#define PATH			"/todos "
#define PATHID			"/todos?id="

#define CONTYPE			"Content-Type: application/json\r\n\r\n"
#define RESP_OK			"HTTP/1.1 200 OK\r\n\r\n"
#define RESP_GETOK		"HTTP/1.1 200 OK\r\n"
#define RESP_DEL		"HTTP/1.1 204 No Content\r\n\r\n"
#define RESP_CREATED		"HTTP/1.1 201 Created\r\n"
#define RESP_NOTFOUND		"HTTP/1.1 404 Not Found\r\n\r\n"
#define RESP_LENREQ		"HTTP/1.1 Length Required\r\n\r\n"
#define RESP_UNPROCESSENT	"HTTP/1.1 422 Unprocessable Entity\r\n\r\n"

#define POST_LEN		strlen(POST)
#define GET_LEN			strlen(GET)
#define DELETE_LEN		strlen(DELETE)

#define RESP_OK_LEN		strlen(RESP_OK)
#define RESP_DEL_LEN		strlen(RESP_DEL)
#define RESP_NOTFOUND_LEN	strlen(RESP_NOTFOUND)
#define RESP_LENREQ_LEN		strlen(RESP_LENREQ)
#define RESP_UNPROCESSENT_LEN	strlen(RESP_UNPROCESSENT)

/**
 * struct todo_list_s - todo linked list
 * @id: member id
 * @title: title string
 * @desc: description string
 * @len: length of json format
 * @next: pointer to next todo node
 */
typedef struct todo_list_s
{
	size_t id;
	char *title;
	char *desc;
	size_t len;
	struct todo_list_s *next;
} todo_list_t;

/**
 * struct todo_info_s - queue for todo linked list
 * @head: pointer to head todo node
 * @tail: pointer to tail todo node
 */
typedef struct todo_info_s
{
	todo_list_t *head;
	todo_list_t *tail;
} todo_info_t;

/* sockets.c */
int init_socket(void);
int accept_recv(int serv_fd, char *buffer, int mode);

/* response.c */
void post_resp(int client_fd, todo_info_t *td_info);
void getall_resp(int client_fd, todo_info_t *td_info);
void get_resp(int client_fd, todo_info_t *td_info, size_t id);
void del_resp(int client_fd, todo_info_t *td_info, size_t id);

#endif /* REST_H */
