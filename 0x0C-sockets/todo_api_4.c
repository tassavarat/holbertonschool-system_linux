#include "rest.h"

/**
 * resp_post - formats str for create response
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
void resp_post(int client_fd, todo_info_t *td_info)
{
	char str[BUFSIZ];
	size_t len = CONSTLEN, resp_len;

	sprintf(str, "%lu", td_info->tail->id);
	len += strlen(str);
	len += strlen(td_info->tail->title);
	len += strlen(td_info->tail->desc);
	printf("POST /todos -> 201 Created\n");
	sprintf(str, "%s%s%lu\r\n%s\r\n\r\n%s%lu%s%s%s%s\"}",
			RESP_CREATED, "Content-Length: ", len,
			"Content-Type: application/json", "{\"id\":",
			td_info->tail->id, ",\"title\":\"",
			td_info->tail->title, "\",\"description\":\"",
			td_info->tail->desc);
	resp_len = strlen(str);
	send(client_fd, str, resp_len, 0);
}

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
		td_info->head = td_info->tail = new;
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
 * parse_req - parse given request
 * @buffer: HTTP request to print
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
void parse_req(char *buffer, int client_fd, todo_info_t *td_info)
{
	char *saveptr;

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
		resp_post(client_fd, td_info);
	}
	else
	{
		strtok_r(buffer, " ", &saveptr);
		printf("method %s -> 404 Not Found\n",
				strtok_r(NULL, " ", &saveptr));
		send(client_fd, RESP_NOTFOUND, RESP_NOTFOUND_LEN, 0);
		return;
	}
	if (parse_req2(buffer, client_fd) == 1)
		return;
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
		client_fd = accept_recv(serv_fd, buffer);
		if (client_fd == -1)
			return (1);
		parse_req(buffer, client_fd, td_info);
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
