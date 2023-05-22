#include "shell.h"

/**
 * _strlen - you need to return with the length of a string
 * @s: to check the length of the string
 *
 * Return: return with the length of a string in integers
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - you must compare two strangs lexicographically.
 * @s1: referes to the first strang
 * @s2: indicates to the second strang
 * Return: return with negative if s1 < s2,
 * return with positive if s1 > s2,
 * return with  zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - evaluates whether the haystack comes before the needle
 * @haystack: refers to the string that needs to be searched for
 *
 * @needle: refers to the substring that need to be found
 * Return: return with address of next char of haystack,
 * or return with  NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - brings together two strings
 * @dest: refers to the destination of the buffer
 *
 * @src: refers to the source of the buffer
 * Return: return with the pointer to the destination of the  buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
