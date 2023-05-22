#include "shell.h"

/**
 * _eputs - prints a string of input
 * @str: string that needs to be printed
 * Return: Nothing
*/

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - adds the letter C to stderr.
 * @c: The text to be printed
 * Return: On success 1.
 * On error, -1 is return, and the proper errno value is set.
*/

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the letter C to the specified fd.
 * @c: print The character
 * @fd: write The filedescriptor
 * Return: On success 1.
 * On error, -1 returned, and the proper value of errno is set.
*/

int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - input string prints
 * @str: a string that will be printed
 * @fd: The address to contact is
 * Return: amount of characters entered
*/

int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
