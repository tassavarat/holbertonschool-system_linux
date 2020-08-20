#include "rest.h"

/**
 * get_resp - formats str for GET response
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
void get_resp(int client_fd, todo_info_t *td_info)
{

}

/**
 * post_resp - formats str for POST response
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
void post_resp(int client_fd, todo_info_t *td_info)
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
	else if (strncmp(buffer, GET, GET_LEN) == 0)
	{
		send(client_fd, RESP_OK, RESP_OK_LEN, 0);
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
		client_fd = accept_recv(serv_fd, buffer);
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
