#include "shell.h"

/**
 * _thechain - To determine whether the current character in the buffer,
 * is a delimiter for a chain, a test is conducted
 * @info: indicates to the parameter of the struct
 *
 * @buf: refers to the char of the buffer
 * @p: character p refers to the address of the current position in the buffer
 *
 * Return: return with 1 if you managed to chain the delimeter,
 * return with 0 if otherwise
 */
int _thechain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * examine_thechain - based on last status checks, chaining should be continued
 * @info: indicates to the parameter of the struct
 *
 * @buf: refers to the char of the buffer
 *
 * @p: character p refers to the address of the current position in the buffer
 * @i: character i indicates to the starting position in the buffer
 *
 * @len: this refers to the length of the buffer
 * Return: you should return wiht Void
 */
void examine_thechain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * substitute_thealias - refers to the alias that must be replaced,
 * in the tokenized string
 *
 * @info: indicates to the parameter of the struct
 *
 * Return: return with 1 if you manage to replace,
 * return with 0 otherwise
 */
int substitute_thealias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = thenode_begin_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strch(node->str, '=');
		if (!p)
			return (0);
		p = strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * substitute_thevars - refers to the vars that must be replaced,
 * in the tokenized string
 * @info: indicates to the parameter of the struct
 *
 * Return: return with 1 if you manage to replace,
 * return with 0 otherwise
 */
int substitute_thevars(info_t *info)
{
	 int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_compareandstrcmp(info->argv[i], "$?"))

		{
			substitute_thestring(&(info->argv[i]),
					strdup(change_number(info->status, 10, 0)));
			continue;
		}
		if (!_compareandstrcmp(info->argv[i], "$$"))
		{
			substitute_thestring(&(info->argv[i]),
					strdup(change_number(getpid(), 10, 0)));
			continue;
		}
		node = thenode_begin_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			substitute_thestring(&(info->argv[i]),
					strdup(_strch(node->str, '=') + 1));
			continue;
		}
		substitute_thestring(&info->argv[i], strdup(""));

	}
	return (0);
}

/**
 * substitute_thestring - a string must be replaced
 * @old: refers to the address of an old string
 * @new: indicates to the new string
 *
 * Return: return with 1 if you managed to replace,
 * return with 0 if otherwise
 */
int substitute_thestring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
