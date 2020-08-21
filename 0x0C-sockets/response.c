#include "rest.h"

/**
 * del_resp - delete specified member and responds to client
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 * @id: id to get
 */
void del_resp(int client_fd, todo_info_t *td_info, size_t id)
{
	todo_list_t *cur, *tmp;

	for (cur = td_info->head; cur && cur->id != id; cur = cur->next)
	{
		if (cur->next && id == cur->next->id)
			break;
	}
	if (!cur)
	{
		printf("%s /todos -> 404 Not Found\n", DELETE);
		send(client_fd, RESP_NOTFOUND, RESP_NOTFOUND_LEN, 0);
		return;
	}
	if (cur == td_info->head)
	{
		cur = cur->next;
		free(td_info->head);
		td_info->head = cur;
	}
	else if (cur->next == td_info->tail)
	{
		cur->next = NULL;
		free(td_info->tail);
		td_info->tail = cur;
	}
	else
	{
		tmp = cur->next;
		cur->next = tmp->next;
		free(tmp);
	}
	printf("%s /todos -> 204 No content\n", DELETE);
	send(client_fd, RESP_DEL, RESP_DEL_LEN, 0);
}

/**
 * get_resp - formats str for GET response
 * @client_fd: client file descriptor
 * @td_info: info for todo linked list
 * @id: id to get
 */
void get_resp(int client_fd, todo_info_t *td_info, size_t id)
{
	todo_list_t *cur;
	char str[BUFSIZ];

	for (cur = td_info->head; cur && cur->id != id; cur = cur->next)
		;
	if (!cur)
	{
		printf("%s -> 404 Not Found\n", GET);
		send(client_fd, RESP_NOTFOUND, RESP_NOTFOUND_LEN, 0);
		return;
	}
	sprintf(str, "%s%s%lu\r\n%s%s%lu%s%s%s%s\"}", RESP_GETOK,
			"Content-Length: ", cur->len, CONTYPE,
			"{\"id\":", cur->id, ",\"title\":\"",
			cur->title, "\",\"description\":\"",
			cur->desc);
	printf("GET /todos -> 200 OK\n");
	send(client_fd, str, strlen(str), 0);
}

/**
 * getall_resp - formats str for GET all response
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
