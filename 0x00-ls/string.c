#include "hls.h"

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

/**
 * _strdup - Returns pointer to newly allocated space which contains a string
 * @str: String to be copied
 *
 * Return: Pointer to new string identical to str, NULL if str = NULL
 */
char *_strdup(char *str)
{
	char *s;
	int i;
	int len;

	i = 0;
	if (!str)
		return (NULL);
	while (*(str + i))
		++i;
	len = i;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	for (i = 0; i <= len; ++i)
		*(s + i) = *(str + i);
	return (s);
}
