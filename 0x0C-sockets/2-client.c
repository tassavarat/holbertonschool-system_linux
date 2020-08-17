#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * error - close file descriptor and exit program
 * @fd: file descriptor to close
 * @res: addrinfo to free
 */
void error(int fd, struct addrinfo *res)
{
	close(fd);
	freeaddrinfo(res);
	exit(1);
}

/**
 * main - entry point for connecting to listening server
 * @argc: number of command-line arguments
 * @argv: command-line arguments containing host and port to connect to
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	char host[254];
	struct addrinfo hints, *res;
	int sfd;

	if (argc  != 3)
	{
		fprintf(stderr, "Usage: %s <host> <port>\n", *argv);
		return (EXIT_FAILURE);
	}
	if (gethostname(host, 254) == -1)
		return (EXIT_FAILURE);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(host, argv[2], &hints, &res) != 0)
		return (EXIT_FAILURE);
	sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sfd == -1)
		error(sfd, res);
	if (connect(sfd, res->ai_addr, res->ai_addrlen) == -1)
		error(sfd, res);
	printf("Connected to %s:%s\n", argv[1], argv[2]);
	freeaddrinfo(res);
	close(sfd);
	return (EXIT_SUCCESS);
}
