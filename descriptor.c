#include "shell.h"

/**
 * is_chain - To determine whether the current character in the buffer,
 * is a delimiter for a chain, a test is conducted
 * @info: indicates to the parameter of the struct
 *
 * @buf: refers to the char of the buffer
 * @p: character p refers to the address of the current position in the buffer
 *
 * Return: return with 1 if you managed to chain the delimeter,
 * return with 0 if otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
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
 * check_chain - based on last status checks, chaining should be continued
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
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
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
 * replace_alias - refers to the vars that must be replaced,
 * in the tokenized string
 *
 * @info: indicates to the parameter of the struct
 *
 * Return: return with 1 if you manage to replace,
 * return with 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - refers to the vars that must be replaced,
 * in the tokenized string
 * @info: indicates to the parameter of the struct
 *
 * Return: return with 1 if you manage to replace,
 * return with 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - a string must be replaced
 * @old: refers to the address of an old string
 * @new: indicates to the new string
 *
 * Return: return with 1 if you managed to replace,
 * return with 0 if otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
