#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * error - close file descriptor and exit program
 * @serv_fd: file descriptor to close
 * @client_fd: file descriptor to close
 */
void error(int serv_fd, int client_fd)
{
	close(serv_fd);
	if (client_fd != -1)
		close(client_fd);
	exit(1);
}

/**
 * main - open IPv4 socket, listens, accepts, and prints recv message
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int serv_fd, client_fd = -1, port;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addrlen;
	char buffer[BUFSIZ];

	serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_fd == -1)
		error(serv_fd, client_fd);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	port = 12345;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(serv_fd, (struct sockaddr *)&server_addr,
				sizeof(server_addr)) == -1)
		error(serv_fd, client_fd);
	if (listen(serv_fd, 10) == -1)
		error(serv_fd, client_fd);
	printf("Server listening on port %i\n", port);
	client_addrlen = sizeof(client_addr);
	client_fd = accept(serv_fd, (struct sockaddr *) &client_addr,
			&client_addrlen);
	if (client_fd == -1)
		error(serv_fd, client_fd);
	printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
	if (recv(client_fd, buffer, BUFSIZ, 0) == -1)
		error(serv_fd, client_fd);
	close(client_fd);
	close(serv_fd);
	printf("Message received: \"%s\"\n", buffer);
	return (0);
}
