#include "hls.h"

int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return (s1[i] - s2[i]);
}

char *str_toupper(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= ' ';
	return (s);
}

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i]; ++i)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

int cmpstringp(const char *p1, const char *p2)
{
	char tp1[256];
	char tp2[256];

	str_toupper(_strcpy(tp1, p1));
	str_toupper(_strcpy(tp2, p2));
	return (_strcmp(tp1, tp2));
}
