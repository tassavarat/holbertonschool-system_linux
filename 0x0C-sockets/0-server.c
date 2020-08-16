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
 * main - open IPv4 socket and listens to traffic on part 12345
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	int sfd, port = 12345;
	struct sockaddr_in addr;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
		error(sfd);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		error(sfd);
	if (listen(sfd, 10) == -1)
		error(sfd);
	printf("Server listening on port %i\n", port);
	pause();
	return (0);
}
