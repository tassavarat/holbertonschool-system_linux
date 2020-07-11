#include "multithreading.h"

pthread_mutex_t mutex;

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
	int c;

	if (pthread_mutex_lock(&mutex) != 0)
		perror(NULL);
	c = printf("[%lu] %s", pthread_self(), format);
	if (pthread_mutex_unlock(&mutex) != 0)
		perror(NULL);
	return (c);
}
