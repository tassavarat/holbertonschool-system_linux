#include "rest.h"

/**
 * get_resp - formats str for GET response
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
/* HTTP/1.1 200 OK^M$ */
/* Content-Length: 2^M$ */
/* Content-Type: application/json^M$ */
/* ^M$ */
/* []alex@~/0x0C-sockets$ */
void get_resp(int client_fd, todo_info_t *td_info)
{
	char str[BUFSIZ];
	size_t resp_len = 2;

	if (td_info->head == NULL)
		sprintf(str, "%s%s%lu\r\n%s[]", RESP_GETOK, "Content-Length: ",
				resp_len, CONTYPE);
	send(client_fd, str, RESP_OK_LEN, 0);
}
/* send(client_fd, RESP_OK, RESP_OK_LEN, 0); */

/**
 * post_resp - formats str for POST response
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
void post_resp(int client_fd, todo_info_t *td_info)
{
	char str[BUFSIZ];
	size_t len = CONSTLEN;

	sprintf(str, "%lu", td_info->tail->id);
	len += strlen(str) + strlen(td_info->tail->title) +
		strlen(td_info->tail->desc);
	printf("POST /todos -> 201 Created\n");
	sprintf(str, "%s%s%lu\r\n%s%s%lu%s%s%s%s\"}", RESP_CREATED,
			"Content-Length: ", len, CONTYPE, "{\"id\":",
			td_info->tail->id, ",\"title\":\"",
			td_info->tail->title, "\",\"description\":\"",
			td_info->tail->desc);
	send(client_fd, str, strlen(str), 0);
}
