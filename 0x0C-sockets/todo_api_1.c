#include "rest.h"

/**
 * print_query - print request path and all query key/value pairs
 * @buffer: HTTP request to print
 */
void print_query(char *buffer)
{
	char *saveptr, *token, *val;

	strtok_r(buffer, " ", &saveptr);
	token = strtok_r(NULL, "?", &saveptr);
	printf("Path: %s\n", token);
	while (1)
	{
		token = strtok_r(NULL, "=", &saveptr);
		val = strtok_r(NULL, "& ", &saveptr);
		if (val == NULL)
			break;
		printf("Query: \"%s\" -> \"%s\"\n", token, val);
	}
}

/**
 * accept_connection - accept connections, print, and sends HTTP/1.1 request
 * @serv_fd: server file descriptor
 *
 * Return: 0 on success, 1 on error
 */
int accept_connection(int serv_fd)
{
	int client_fd;
	char buffer[BUFSIZ];

	while (1)
	{
		client_fd = accept_recv(serv_fd, buffer, VERBOSE_ON);
		if (client_fd == -1)
			return (1);
		print_query(buffer);
		send(client_fd, RESP_OK, RESP_OK_LEN, 0);
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

	setbuf(stdout, NULL);
	serv_fd = init_socket();
	if (serv_fd == -1)
		return (1);
	ret = accept_connection(serv_fd);
	close(serv_fd);
	return (ret);
}
