#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * error - close file descriptor and exit program
 * @fd: file descriptor to close
 */
void error(int fd)
{
	close(fd);
	exit(1);
}

/**
 * main - open IPv4 socket, listens, and accepts entering connection
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int sfd, port;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addrlen;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
		error(sfd);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	port = 12345;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
			-1)
		error(sfd);
	if (listen(sfd, 10) == -1)
		error(sfd);
	printf("Server listening on port %i\n", port);
	client_addrlen = sizeof(client_addr);
	if (accept(sfd, (struct sockaddr *) &client_addr, &client_addrlen) ==
			-1)
		error(sfd);
	printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
	close(sfd);
	return (0);
}
