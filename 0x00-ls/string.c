#include "hls.h"

/**
 * _memcpy - Copies memory area
 * @dest: Area being copied to
 * @src: Area being copied
 * @n: Amount of bytes to be copied
 *
 * Return: Pointer to dest
 */
char *_memcpy(char *dest, char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n; ++i)
		dest[i] = src[i];
	return (dest);
}

/**
 * _strlen - gets length of a string
 * @s: string to count
 *
 * Return: length
 */
size_t _strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: positive or negative value whether p1 or p2 are greater
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return (s1[i] - s2[i]);
}

/**
 * str_toupper - converts lowercase letters to uppercase
 * @s: string to convert
 *
 * Return: converted string
 */
char *str_toupper(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= ' ';
	return (s);
}

/**
 * _strcpy - copies a string
 * @dest: buffer being copied to
 * @src: pointer to string being copied
 *
 * Return: pointer to destination string dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i]; ++i)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
