#include "rest.h"

/**
 * get_resp - formats str for GET response
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
void getall_resp(int client_fd, todo_info_t *td_info)
{
	char str1[BUFSIZ * 2], str2[BUFSIZ] = {'\0'};
	todo_list_t *cur;
	size_t len = GET_CONSTLEN;

	if (td_info->head == NULL)
	{
		sprintf(str1, "%s%s%i\r\n%s[]", RESP_GETOK, "Content-Length: ",
				GET_CONSTLEN, CONTYPE);
	}
	else
	{
		for (cur = td_info->head; cur != NULL; cur = cur->next)
		{
			len += cur->len;
			if (cur != td_info->head)
			{
				++len;
				sprintf(str1, ",%s%lu%s%s%s%s\"}", "{\"id\":",
						cur->id, ",\"title\":\"",
						cur->title,
						"\",\"description\":\"",
						cur->desc);
				strcat(str2, str1);
			}
		}
		sprintf(str1, "%s%s%lu\r\n%s[%s%lu%s%s%s%s\"}%s]",
				RESP_GETOK, "Content-Length: ",
				len, CONTYPE, "{\"id\":", td_info->head->id,
				",\"title\":\"", td_info->head->title,
				"\",\"description\":\"", td_info->head->desc,
				str2);
	}
	printf("GET /todos -> 200 OK\n");
	send(client_fd, str1, strlen(str1), 0);
}

/**
 * post_resp - formats str for POST response
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
void post_resp(int client_fd, todo_info_t *td_info)
{
	char str[BUFSIZ];

	sprintf(str, "%lu", td_info->tail->id);
	td_info->tail->len = strlen(str) + strlen(td_info->tail->title) +
		strlen(td_info->tail->desc) + POST_CONSTLEN;
	sprintf(str, "%s%s%lu\r\n%s%s%lu%s%s%s%s\"}", RESP_CREATED,
			"Content-Length: ", td_info->tail->len, CONTYPE,
			"{\"id\":", td_info->tail->id, ",\"title\":\"",
			td_info->tail->title, "\",\"description\":\"",
			td_info->tail->desc);
	printf("POST /todos -> 201 Created\n");
	send(client_fd, str, strlen(str), 0);
}
