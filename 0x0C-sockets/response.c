#include "rest.h"

/**
 * get_resp - formats str for GET response
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 */
void get_resp(int client_fd, todo_info_t *td_info)
{
	char str1[BUFSIZ], str2[BUFSIZ];
	/* char str1[BUFSIZ]; */
	todo_list_t *cur;

	for (cur = td_info->head; cur != NULL; cur = cur->next)
	{
		printf("ID: %lu\n", cur->id);
		printf("TARGET: %lu\n", cur->len);
	}
	if (td_info->head == NULL)
	{
		sprintf(str1, "%s%s%i\r\n%s[]", RESP_GETOK, "Content-Length: ",
				GET_CONSTLEN, CONTYPE);
	}
	else
	{
		sprintf(str1, "%s%s%lu\r\n%s[%s%lu%s%s%s%s\"}]",
				RESP_GETOK, "Content-Length: ",
				td_info->head->len + GET_CONSTLEN, CONTYPE,
				"{\"id\":", td_info->head->id, ",\"title\":\"",
				td_info->head->title, "\",\"description\":\"",
				td_info->head->desc);
		for (cur = td_info->head->next; cur != NULL; cur = cur->next)
		{
			/* sprintf(str2, "%lu", td_info->head->id); */
			/* len += strlen(str2) + strlen(td_info->head->title) + */
			/* 	strlen(td_info->head->desc); */
			sprintf(str2, ",%s%s%lu\r\n%s[%s%lu%s%s%s%s\"}]",
					RESP_GETOK, "Content-Length: ",
					cur->len + GET_CONSTLEN + 1, CONTYPE,
					"{\"id\":", cur->id, ",\"title\":\"",
					cur->title, "\",\"description\":\"",
					cur->desc);
			strcat(str1, str2);
		}
	}
	printf("GET /todos -> 200 OK\n");
	send(client_fd, str1, strlen(str1), 0);
}
/* send(client_fd, RESP_OK, RESP_OK_LEN, 0); */
/* [{"id":0,"title":"Dishes","description":"Not_really_urgent"},{"id":1,"title":"Laundry","description":"To_be_done_by_yesterday"}] */

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
