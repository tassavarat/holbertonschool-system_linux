#include "multithreading.h"

/**
 * tprintf - print out given formatted string
 * @format: string to print
 *
 * Return: printf return value
 */
int tprintf(char const *format, ...)
{
	va_list ap;
	int c;

	va_start(ap, format);
	c = printf("[%lu] ", pthread_self());
	c += vprintf(format, ap);
	va_end(ap);
	return (c);
}
