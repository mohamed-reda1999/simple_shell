#include "shell.h"

/**
 * _copystring - a string is copied
 * @dest: referes to the destination
 *
 * @src: indicates to the source
 *
 * Return: you must return with pointer to the destination
 */
char *_copystring(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _duplicator - a string must be duplicated
 *
 * @str: refers to he string that must be duplicated
 *
 * Return: return with thepointer of duplicated string
 */
char *_duplicator(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _adds - you must print input of the string
 *
 * @str: refers to the string that should be printed
 *
 * Return: return with nothing
 */
void _adds(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _coverter - Incorporates the letter C into the stdout stream
 * @c: C is the character to  be printed
 *
 * Return: return with 1 when you succeed,
 * return with -1 on error, and errno is set correctly.
 */
int _converter(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
