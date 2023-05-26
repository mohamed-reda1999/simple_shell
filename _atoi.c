#include "shell.h"

/**
 * interactive - if the shell is in interactive mode, returns true
 * @info:  address struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * delim - determines whether a character is a delimeter
 * @c:  check the char
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * alpha - makes an alphabetic character chec
 * @c:  input the char
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _toi - creates an integer from a string
 * @s: converted the string
 * Return: 0 number transformed if there are no numbers in the string
 */

int _toi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
