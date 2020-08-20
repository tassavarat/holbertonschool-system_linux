#include "rest.h"

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
