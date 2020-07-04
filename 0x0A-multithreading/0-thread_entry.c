#include "multithreading.h"

/**
 * thread_entry - entry point to new thread
 * @arg: pointer to argument for thread
 *
 * Return: NULL pointer
 */
void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);
	pthread_exit(NULL);
}
