#include "multithreading.h"

/**
 * tprintf - print out given formatted string
 * @format: string to print
 *
 * Return: printf return value
 */
int tprintf(char const *format, ...)
{
	return (printf("[%lu] %s", pthread_self(), format));
}
