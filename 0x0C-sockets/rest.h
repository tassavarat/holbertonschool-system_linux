#ifndef REST_H
#define REST_H

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

/* sockets.c */
int init_socket(void);
int accept_recv(int serv_fd, char *buffer);

#endif /* REST_H */
