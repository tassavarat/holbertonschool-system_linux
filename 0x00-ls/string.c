#include "hls.h"

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

/**
 * cmpstringp - copies strings to buffers and compares them regardless of case
 * @p1: first string
 * @p2: second string
 *
 * Return: positive or negative value whether p1 or p2 are greater
 */
int cmpstringp(const char *p1, const char *p2)
{
	char tp1[256];
	char tp2[256];

	str_toupper(_strcpy(tp1, p1));
	str_toupper(_strcpy(tp2, p2));
	return (_strcmp(tp1, tp2));
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
