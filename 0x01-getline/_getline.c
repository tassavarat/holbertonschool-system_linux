#include "_getline.h"

/**
 * linknode - links nodes together
 * @head: pointer to pointer to head node of linked list
 * @new: new node to link
 */
void linknode(listchar **head, listchar *new)
{
	listchar **cur;

	cur = head;
	while (*cur)
		cur = &(*cur)->next;
	new->next = *cur;
	*cur = new;
}

/**
 * createnode - creates new linked list node
 * @src: string
 * @end: bytes to copy
 * @lstfd: if creating listfd node
 * @fd: file descriptor
 *
 * Return: created linked list node
 */
void *createnode(char *src, size_t end, size_t lstfd, int fd)
{
	void *new;

	if (!lstfd)
	{
		static size_t line = 1;

		new = (listchar *) malloc(sizeof(listchar));
		if (!new)
			return (NULL);
		((listchar *) new)->line = line;
		++line;
		((listchar *) new)->s = malloc((end + 1) * sizeof(char));
		memcpy(((listchar *) new)->s, src, end);
		((listchar *) new)->s[end] = '\0';
		((listchar *) new)->size = end + 1;
		((listchar *) new)->next = NULL;
	}
	else
	{
		new = (listfd *) malloc(sizeof(listfd));
		((listfd *) new)->fd = fd;
		((listfd *) new)->head = NULL;
	}
	return (new);
}

/**
 * parseline - stores each line as a linked list
 * @file: string of entire file
 * @head: pointer to pointer to head node of linked list
 */
void parseline(char *file, listchar **head)
{
	size_t i, start;

	start = 0;
	for (i = 0; file[i]; ++i)
		if (file[i] == '\n')
		{
			linknode(head, createnode(&file[start], i - start, 0, 0));
			start = i + 1;
		}
	if (file[start])
		linknode(head, createnode(&file[start], i - start, 0, 0));
}

/**
 * _realloc - changes the size of the memory to new_size bytes
 * @ptr: pointer to memory block
 * @old_size: old size of memory block
 * @new_size: new size of memory block
 *
 * Return: pointer to newly allocated memory
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *newptr;

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
 * _getline - reads an entire line from a file descriptor
 * @fd: file descriptor to read from
 *
 * Return: null-terminated string excluding newline character
 * NULL on EOF or error
 */
char *_getline(const int fd)
{
	char buf[READ_SIZE] = {0};
	char *file, *line;
	size_t linsiz,  rd;
	ssize_t byte;
	listchar *tmp;
	static listchar *head;

	rd = 0;
	linsiz = READ_SIZE + 1;
	file = malloc(linsiz * sizeof(*file));
	if (!file)
		return (NULL);
	memset(file, 0, linsiz * sizeof(*file));
	while ((byte = read(fd, buf, READ_SIZE)) > 0)
	{
		_strncat(file, buf, READ_SIZE);
		linsiz += READ_SIZE;
		file = _realloc(file, linsiz - READ_SIZE, linsiz * sizeof(*file));
		memset(buf, 0, READ_SIZE * sizeof(*buf));
		rd = 1;
	}
	if (rd)
		parseline(file, &head);
	free(file);
	if (!head)
		return (NULL);
	tmp = head;
	head = head->next;
	line = malloc(tmp->size * sizeof(*line));
	memcpy(line, tmp->s, tmp->size);
	free(tmp->s);
	free(tmp);
	return (line);
}
