#include "rest.h"

/**
 * post - create given todo
 * @buffer: raw HTTP request
 * @td_info: info for todo linked list
 *
 * Return: created todo node, NULL on error
 */
todo_list_t *post(char *buffer, todo_info_t *td_info)
{
	char *saveptr, *token, *title, *desc;
	int i;
	todo_list_t *new;

	for (i = 0, strtok_r(buffer, "\n", &saveptr); i < 7; ++i)
		token = strtok_r(NULL, "\n", &saveptr);
	title = strstr(token, "title");
	if (!title)
		return (NULL);
	desc = strstr(token, "description");
	if (!desc)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
	{
		perror("malloc failed");
		exit(1);
	}
	strtok_r(title, "=", &saveptr);
	new->title = strdup(strtok_r(NULL, "&\0", &saveptr));
	strtok_r(desc, "=", &saveptr);
	new->desc = strdup(strtok_r(NULL, "&\0", &saveptr));
	if (td_info->head == NULL)
	{
		new->id = 0;
		td_info->head = new;
		td_info->tail = new;
	}
	else
	{
		new->id = td_info->tail->id + 1;
		td_info->tail->next = new;
		td_info->tail = new;
	}
	new->next = NULL;
	return (new);
}

/**
 * parse_error - parse request errors
 * @buffer: HTTP request to print
 * @client_fd: client file descriptor
 *
 * Return: 0 on success, 1 on error
 */
int parse_error(char *buffer, int client_fd)
{
	char *saveptr;

	if (strstr(buffer, PATH) == NULL)
	{
		strtok_r(buffer, " ", &saveptr);
		printf("%s %s -> 404 Not Found\n", POST,
				strtok_r(NULL, " ", &saveptr));
		send(client_fd, RESP_NOTFOUND, RESP_NOTFOUND_LEN, 0);
		return (1);
	}
	if (strstr(buffer, "Content-Length") == NULL)
	{
		strtok_r(buffer, " ", &saveptr);
		printf("%s %s -> 411 Length Required\n", POST,
				strtok_r(NULL, " ", &saveptr));
		send(client_fd, RESP_LENREQ, RESP_LENREQ_LEN, 0);
		return (1);
	}
	return (0);
}

/**
 * parse_req - parse given request
 * @buffer: HTTP request to print
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
void parse_req(char *buffer, int client_fd, todo_info_t *td_info)
{
	char *saveptr;

	if (parse_error(buffer, client_fd) == 1)
		return;
	if (strncmp(buffer, POST, POST_LEN) == 0)
	{
		if (post(buffer, td_info) == NULL)
		{
			strtok_r(buffer, " ", &saveptr);
			printf("%s %s -> 422 Unprocessable Entity\n", POST,
					strtok_r(NULL, " ", &saveptr));
			send(client_fd, RESP_UNPROCESSENT,
					RESP_UNPROCESSENT_LEN, 0);
			return;
		}
		post_resp(client_fd, td_info);
	}
	else
	{
		strtok_r(buffer, " ", &saveptr);
		printf("method %s -> 404 Not Found\n",
				strtok_r(NULL, " ", &saveptr));
		send(client_fd, RESP_NOTFOUND, RESP_NOTFOUND_LEN, 0);
		return;
	}
}

/**
 * accept_connection - accept connections, print, and sends HTTP/1.1 request
 * @serv_fd: server file descriptor
 * @td_info: info for todo linked list
 *
 * Return: 0 on success, 1 on error
 */
int accept_connection(int serv_fd, todo_info_t *td_info)
{
	int client_fd;
	char buffer[BUFSIZ];

	while (1)
	{
		client_fd = accept_recv(serv_fd, buffer, VERBOSE_OFF);
		if (client_fd == -1)
			return (1);
		parse_req(buffer, client_fd, td_info);
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
	todo_info_t *td_info;

	td_info = malloc(sizeof(*td_info));
	if (td_info == NULL)
		return (1);
	td_info->head = td_info->tail = NULL;
	setbuf(stdout, NULL);
	serv_fd = init_socket();
	if (serv_fd == -1)
		return (1);
	ret = accept_connection(serv_fd, td_info);
	close(serv_fd);
	return (ret);
}
