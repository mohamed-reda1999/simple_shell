#include "shell.h"

/**
 * _err - creates an integer from a string
 * @s: the string being transformed
 * Return: 0 number transformed if there are no numbers in the string.
 *       -1 on error
*/

int _err(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * echo_error - prints a message in error
 * @info: struct for argument and return information
 * @estr: string with the indicated error type
 * Return: 0 number transformed if there are no numbers in the string.
 *        -1 on error
*/

void echo_error(info_t *info, char *estr)
{
	_eput(info->fname);
	_eput(": ");
	echo_int(info->line_count, STDERR_FILENO);
	_eput(": ");
	_eput(info->argv[0]);
	_eput(": ");
	_eput(estr);
}

/**
 * echo_int - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: The address to contact is
 * Return: Character count on the page
*/

int echo_int(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputint;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * change_number - a converter function that mimics itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
*/

char *change_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * delete_comments - function swaps out the initial instance of '#' with '\0'
 * @buf: address of the modified string
 * Return: Always 0;
*/

void delete_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
