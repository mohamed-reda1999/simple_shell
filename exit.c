#include "shell.h"

/**
 **_strncpy - string copies
 *@dest: the string to be copied to at the destination
 *@src: source string
 *@n: the number of characters that must be copied
 *Return: the concatenated string
*/

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - joins two strings together.
 *@dest: string first
 *@src: string second
 *@n: the maximum number of bytes to be used
 *Return: the concatenated string
*/

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - seeks out a character within a string
 *@s: to be parsed is the string
 *@c: the person to watch out for
 *Return: (s) a reference to the memory space
*/

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
