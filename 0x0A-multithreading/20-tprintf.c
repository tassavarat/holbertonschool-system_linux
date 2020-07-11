#include "multithreading.h"

static pthread_mutex_t mutex;

/**
 * mutex_destroy - destroy mutex
 */
__attribute__((destructor))void mutex_destroy(void)
{
	if (pthread_mutex_destroy(&mutex))
		perror(NULL);
}

/**
 * mutex_init - initialise mutex
 */
__attribute__((constructor))void mutex_init(void)
{
	if (pthread_mutex_init(&mutex, NULL) != 0)
		perror(NULL);
}

/**
 * tprintf - print out given formatted string
 * @format: string to print
 *
 * Return: number of characters printed
 */
int tprintf(char const *format, ...)
{
	va_list ap;
	int c;

	if (pthread_mutex_lock(&mutex) != 0)
		perror(NULL);
	va_start(ap, format);
	c = printf("[%lu] ", pthread_self());
	c += vprintf(format, ap);
	va_end(ap);
	if (pthread_mutex_unlock(&mutex) != 0)
		perror(NULL);
	return (c);
}
