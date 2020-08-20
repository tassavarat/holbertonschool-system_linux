#include "rest.h"

/**
 * resp_post - formats str for create response
 * @client_fd: client file descriptor
 * @queue: queue for todo linked list
 */
void resp_post(int client_fd, todo_queue_t *queue)
{
	char str[BUFSIZ];
	size_t len = CONSTLEN, resp_len;

	sprintf(str, "%lu", queue->tail->id);
	len += strlen(str);
	len += strlen(queue->tail->title);
	len += strlen(queue->tail->desc);
	printf("POST /todos -> 201 Created\n");
	sprintf(str, "%s%s%lu\r\n%s\r\n\r\n%s%lu%s%s%s%s\"}",
			RESP_CREATED, "Content-Length: ", len,
			"Content-Type: application/json", "{\"id\":",
			queue->tail->id, ",\"title\":\"", queue->tail->title,
			"\",\"description\":\"", queue->tail->desc);
	resp_len = strlen(str);
	send(client_fd, str, resp_len, 0);
}

/**
 * post - create given todo
 * @buffer: raw HTTP request
 * @queue: queue for todo linked list
 *
 * Return: created todo node, NULL on error
 */
todo_list_t *post(char *buffer, todo_queue_t *queue)
{
	char *saveptr, *token;
	int i;
	todo_list_t *new;

	new = malloc(sizeof(*new));
	if (!new)
	{
		perror("malloc failed");
		exit(1);
	}
	for (i = 0, strtok_r(buffer, "\n", &saveptr); i < 6; ++i)
		token = strtok_r(NULL, "\n", &saveptr);
	for (i = 0; i < 2; ++i)
	{
		token = strtok_r(NULL, "=", &saveptr);
		if (!token)
			return (NULL);
		token = strtok_r(NULL, "&\"", &saveptr);
		if (!token)
			return (NULL);
		if (i == 0)
			new->title = strdup(token);
		else
			new->desc = strdup(token);
	}
	if (queue->head == NULL)
	{
		new->id = 0;
		queue->head = queue->tail = new;
	}
	else
	{
		new->id = queue->tail->id + 1;
		queue->tail->next = new;
		queue->tail = new;
	}
	new->next = NULL;
	return (new);
}

/**
 * parse_req - parse given request
 * @buffer: HTTP request to print
 * @client_fd: client file descriptor
 * @queue: queue for todo linked list
 */
void parse_req(char *buffer, int client_fd, todo_queue_t *queue)
{
	char *saveptr;

	if (strncmp(buffer, POST, POST_LEN) != 0)
	{
		strtok_r(buffer, " ", &saveptr);
		printf("GET %s -> 504 Not Found\n",
				strtok_r(NULL, " ", &saveptr));
		send(client_fd, RESP_NOTFOUND, RESP_NOTFOUND_LEN, 0);
		return;
	}
	if (strstr(buffer, "/todos") == NULL)
	{
		strtok_r(buffer, " ", &saveptr);
		printf("%s %s -> 404 Not Found\n", POST,
				strtok_r(NULL, " ", &saveptr));
		send(client_fd, RESP_NOTFOUND, RESP_NOTFOUND_LEN, 0);
		return;
	}
	if (strstr(buffer, "Content-Length") == NULL)
	{
		strtok_r(buffer, " ", &saveptr);
		printf("%s %s -> 411 Length Required\n", POST,
				strtok_r(NULL, " ", &saveptr));
		send(client_fd, RESP_LENREQ, RESP_LENREQ_LEN, 0);
		return;
	}
	if (post(buffer, queue) == NULL)
	{
		strtok_r(buffer, " ", &saveptr);
		printf("%s %s -> 422 Unprocessable Entity\n", POST,
				strtok_r(NULL, " ", &saveptr));
		send(client_fd, RESP_UNPROCESSENT, RESP_UNPROCESSENT_LEN, 0);
		return;
	}
	resp_post(client_fd, queue);
}

/**
 * accept_connection - accept connections, print, and sends HTTP/1.1 request
 * @serv_fd: server file descriptor
 * @queue: queue for todo linked list
 *
 * Return: 0 on success, 1 on error
 */
int accept_connection(int serv_fd, todo_queue_t *queue)
{
	int client_fd;
	char buffer[BUFSIZ];

	while (1)
	{
		client_fd = accept_recv(serv_fd, buffer);
		if (client_fd == -1)
			return (1);
		parse_req(buffer, client_fd, queue);
		/* send(client_fd, RESP_OK, RESP_OK_LEN, 0); */
		close(client_fd);
	}
	return (0);
}

/**
 * main - open IPv4 socket, listens, accepts, and prints recv message
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int serv_fd, ret;
	todo_queue_t *queue;

	queue = malloc(sizeof(*queue));
	if (queue == NULL)
		return (1);
	queue->head = queue->tail = NULL;
	setbuf(stdout, NULL);
	serv_fd = init_socket();
	if (serv_fd == -1)
		return (1);
	ret = accept_connection(serv_fd, queue);
	close(serv_fd);
	return (ret);
}
