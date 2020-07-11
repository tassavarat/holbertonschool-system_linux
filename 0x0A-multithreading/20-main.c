/* Description: Use tprintf many times from multiple threads and main thread */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * _thread_entry - Thread entry point. Prints out a string
 *
 * @arg: Unused
 *
 * Return: NULL
 */
void *_thread_entry(__attribute__((unused))void *arg)
{
	tprintf("C\n");
	tprintf("is\n");
	tprintf("fun\n");
	return (NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	pthread_t tid[10];
	int i;

	tprintf("Creating threads\n");
	for (i = 0; i < 10; i++)
	{
		pthread_create(&tid[i], NULL, &_thread_entry, NULL);
		tprintf("Created thread number %d\n", i);
	}

	tprintf("Holberton School\n");
	tprintf("From main thread\n");

	for (i = 0; i < 10; i++)
		pthread_join(tid[i], NULL);

	return (EXIT_SUCCESS);
}
