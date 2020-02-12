#include "_getline.h"

void linknode(listchar **head, listchar *new)
{
	listchar **cur = head;

	while (*cur)
		cur = &(*cur)->next;
	new->next = *cur;
	*cur = new;
}

listchar *createnode(char *src, const size_t end, const int nl)
{
	listchar *new;
	static size_t linenum = 1;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->line = linenum;
	if (nl)
		++linenum;
	new->s = malloc(end + 1);
	memcpy(new->s, src, end);
	new->s[end] = '\0';
	new->size = end + 1;
	new->next = NULL;
	printf("%lu: %s\n", new->line, new->s);
	return (new);
}

int parseline(char *buf, listchar **head, size_t linsiz)
{
	static char *line;
	int nl = 0;
	size_t start = 0, i;
	static size_t linenum = 1;
	listchar *new;

	line = realloc(line, linsiz);
	if (!line)
		return (NOMEM);
	memset(line, '\0', linsiz);
	for (i = 0; i < READ_SIZE; ++i)
	{
		if (buf[i] == '\n')
		{
			new = createnode(buf + start, i - start, 1);
			linknode(head, new);
			if (!new)
				return (NOMEM);
			start = i + 1;
			++linenum;
			nl = 1;
		}
	}
	if (buf[start])
	{
		strncat(line, buf, READ_SIZE);
		/* new = createnode(buf + start, i, 0); */
		if (!new)
			return (NOMEM);
	}
	return (nl);
}

/**
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor to read from
 *
 * Return: null-terminated string excluding newline character
 * NULL on EOF or error
 */
char *_getline(const int fd)
{
	char buf[READ_SIZE] = {'\0'};
	int status;
	size_t linsiz = READ_SIZE + 1;
	ssize_t byte;
	static listchar *head;

	/* status = readline(fd, &head); */
	while ((byte = read(fd, buf, READ_SIZE)) > 0 && !(status = parseline(buf, &head, linsiz)))
	{
		memset(buf, '\0', READ_SIZE);
		linsiz += READ_SIZE;
	}
	if (status == NOMEM)
		printf("NOMEM ERROR\n");
	while (head)
	{
		printf("head->s: %s\n", head->s);
		head = head->next;
	}
	return (NULL);
}
