#include "rest.h"

/**
 * accept_recv - accept connection and receive message from socket
 * @serv_fd: server file descriptor
 * @buffer: array to hold message from socket
 * @mode: specifies whether to print additional information
 *
 * Return: client file descriptor on success, -1 on error
 */
int accept_recv(int serv_fd, char *buffer, int mode)
{
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t client_addrlen = sizeof(client_addr);

	client_fd = accept(serv_fd, (struct sockaddr *) &client_addr,
			&client_addrlen);
	if (client_fd == -1)
	{
		perror("accept failed");
		return (-1);
	}
	memset(&*buffer, 0, BUFSIZ);
	if (recv(client_fd, buffer, BUFSIZ, 0) == -1)
	{
		close(client_fd);
		perror("recv failed");
		return (-1);
	}
	if (mode == VERBOSE_ON)
	{
		printf("Client connected: %s\n",
				inet_ntoa(client_addr.sin_addr));
		printf("Raw request: \"%s\"\n", buffer);
	}
	return (client_fd);
}

/**
 * init_socket - initialises socket to accept connection
 *
 * Return: server file descriptor on success, -1 on error
 */
int init_socket(void)
{
	int serv_fd, optval;
	struct sockaddr_in server_addr;

	serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_fd == -1)
	{
		perror("socket failed");
		return (-1);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	optval = 1;
	setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (bind(serv_fd, (struct sockaddr *)&server_addr,
				sizeof(server_addr)) == -1)
	{
		perror("bind failed");
		goto out_close_fd;
	}
	if (listen(serv_fd, BACKLOG) == -1)
	{
		perror("listen failed");
		goto out_close_fd;
	}
	printf("Server listening on port %i\n", PORT);
	return (serv_fd);
out_close_fd:
	close(serv_fd);
	return (-1);
}
