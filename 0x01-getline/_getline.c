#include "_getline.h"

static int rd;
static size_t numfd;
static listfd *fdhead;

/**
 * linknode - links nodes together
 * @head: pointer to pointer to head node of linked list
 * @new: new node to link
 * @sort: whether to sort
 */
void linknode(void *head, void *new, size_t sort)
{
	listchar **cur;
	listfd **fdcur;

	if (!sort)
	{
		cur = (listchar **) head;
		while (*cur)
			cur = &(*cur)->next;
		((listchar *) new)->next = *cur;
		*cur = new;
	}
	else
	{
		fdcur = (listfd **) head;
		while (*fdcur && ((listfd *) new)->fd > (*fdcur)->fd)
			fdcur = &(*fdcur)->next;
		((listfd *) new)->next = *fdcur;
		*fdcur = new;
	}
}

/**
 * createnode - creates new linked list node
 * @src: string
 * @end: bytes to copy
 * @nl: whether to increment line number
 * @lstfd: if creating listfd node
 * @fd: file descriptor
 *
 * Return: created linked list node
 */
void *createnode(char *src, size_t end, int nl, size_t lstfd, int fd)
{
	void *new;

	if (!lstfd)
	{
		static size_t line = 1;

		new = (listchar *) malloc(sizeof(listchar));
		if (!new)
			return (NULL);
		((listchar *) new)->line = line;
		if (nl)
			++line;
		((listchar *) new)->s = malloc((end + 1));
		if (!new)
			return (NULL);
		memcpy(((listchar *) new)->s, src, end);
		((listchar *) new)->s[end] = '\0';
		((listchar *) new)->size = end + 1;
		((listchar *) new)->next = NULL;
		/* printf("%lu: %s\n", ((listchar *) new)->line, ((listchar *) new)->s); */
	}
	else
	{
		new = (listfd *) malloc(sizeof(listfd));
		if (!new)
			return (NULL);
		((listfd *) new)->fd = fd;
		((listfd *) new)->head = NULL;
		((listfd *) new)->next = NULL;
	}
	return (new);
}

/**
 * realloc_parse - changes the size of the memory to new_size or parse lines
 * @ptr: pointer to memory block
 * @old_size: old size of memory block
 * @new_size: new size of memory block
 * @parseline: whether to parseline
 * @file: string of entire file
 * @head: pointer to pointer to head node of linked list
 *
 * Return: pointer to newly allocated memory
 */
void *realloc_parse(void *ptr, size_t old_size, size_t new_size,
		size_t parseline, char *file, listchar **head)
{
	void *newptr;
	size_t i, start;
	listchar *new;

	if (parseline)
	{
		for (start = i = 0; file[i]; ++i)
			if (file[i] == '\n')
			{
				new = createnode(&file[start], i - start, 1, 0, 0);
				linknode(head, new, 0);
				start = i + 1;
			}
		if (file[start])
		{
			new = createnode(&file[start], i - start, 0, 0, 0);
			linknode(head, new, 0);
		}
		if (!new)
			return ((char *) NULL);
	}
	else
	{
		if (new_size == 0)
		{
			free(ptr);
			return (NULL);
		}
		if (!ptr)
			return (malloc(new_size));
		if (new_size <= old_size)
			return (ptr);
		newptr = malloc(new_size);
		if (newptr)
		{
			memcpy(newptr, ptr, old_size);
			free(ptr);
		}
	}
	return (newptr);
}

/**
 * _strncat - concatenates two strings to at most n bytes
 * @dest: destination string
 * @src: string to copy
 * @n: amount of bytes to copy
 *
 * Return: pointer to resulting string dest
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len;
	size_t i;

	for (i = 0; dest[i]; ++i)
		;
	dest_len = i;
	for (i = 0; i < n && src[i]; ++i)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * parsefd - parses given fd and creates appropriate listfd
 * @fdhead: pointer to pointer to fdhead node
 * @fd: file descriptor
 * @file: string to free if necessary
 *
 * Return: newly created or matching listfd
 */
listfd *parsefd(listfd **fdhead, const int fd, char *file)
{
	listfd *fdcur;
	listchar *cur, *tmp;

	if (fd == -1)
	{
		while (*fdhead)
		{
			cur = (*fdhead)->head;
			while (cur)
			{
				tmp = cur;
				cur = cur->next;
				free(tmp->s);
				free(tmp);
			}
			fdcur = *fdhead;
			*fdhead = (*fdhead)->next;
			free(fdcur);
		}
		free(file);
		return (NULL);
	}
	fdcur = *fdhead;
	while (fdcur)
	{
		if (fd == fdcur->fd)
			break;
		fdcur = fdcur->next;
	}
	if (!fdcur)
	{
		fdcur = createnode('\0', 0, 0, 1, fd);
		if (!fdcur)
			return (NULL);
		linknode(fdhead, fdcur, 1);
		++numfd;
	}
	rd = 0;
	return (fdcur);
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
	size_t linsiz = READ_SIZE + 1;
	char *line, buf[READ_SIZE] = {0}, *file = malloc(linsiz);
	ssize_t byte;
	listfd *fdcur;
	listchar *tmp;

	if (!file)
		return (NULL);
	memset(file, 0, linsiz);
	fdcur = parsefd(&fdhead, fd, file);
	if (!fdcur)
		return (NULL);
	if (!rd)
		for (; (byte = read(fd, buf, READ_SIZE)) > 0; rd = 1)
		{
			_strncat(file, buf, READ_SIZE);
			linsiz += READ_SIZE;
			file = realloc_parse(file, linsiz - READ_SIZE, linsiz, 0, NULL, NULL);
			if (!file)
				return (NULL);
			memset(buf, 0, READ_SIZE);
		}
	if (rd)
		line = realloc_parse(NULL, 0, 0, 1, file, &fdcur->head);
	free(file);
	if (!fdcur->head)
	{
		if (numfd == 1)
			free(fdcur);
		return (NULL);
	}
	tmp = fdcur->head;
	fdcur->head = fdcur->head->next;
	line = malloc(tmp->size);
	if (!line)
		return (NULL);
	memcpy(line, tmp->s, tmp->size);
	free(tmp->s);
	free(tmp);
	return (line);
}
