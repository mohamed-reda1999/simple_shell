#include "shell.h"

/**
 * thelistof_thelen - Defines the length,
 * of this association list
 * @h: you must assign a pointer to the root node
 *
 * Return: You must return with the size of the list
 */
size_t thelistof_thelen(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * makelist_to_thestrings - Provides an array of strings,
 * from list->str.index_list
 *
 * @head: you must assign a pointer to the root node
 *
 * Return: you must return with an array of strings
 */
char **makelist_to_thestrings(list_t *head)
{
	list_t *node = head;
	size_t i = thelistof_thelen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_findthelengthstrlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _copystring(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * echo_thelist - A list_t linked list is printed with all of its contents
 * @h: you must assign a pointer to the root node
 *
 * Return: you must return wwith the size of the list
 */
size_t echo_thelist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_adds(change_number(h->num, 10, 0));
		_converter(':');
		_converter(' ');
		_adds(h->str ? h->str : "(nil)");
		_adds("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * thenode_begin_with - Rreturns a node whose string prefix,
 * is the first element
 * @node: list head is indicated by a pointer
 * @prefix: Match the string's direction
 * @c: The subsequent character that comes after a given prefix to a match
 *
 * Return: return when you match the node or null
 */
list_t *thenode_begin_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begins_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - receives a node's index
 *
 * @head: list head is indicated by a pointer
 *
 * @node: you should assign your pointer topoint to the node
 *
 * Return: you should return with index of node or return with -1
 */
ssize_t gets_thenode_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
