#include "shell.h"

/**
 * append_node - A node must be added at the beginning of the list
 *
 * @head: you should assign the pointer to the head node
 * @str: indicates to the sequence of characters assigned,
 * to field of node refered as str
 * @num: the number indicates to history's node index node
 * Return: return when find the size of the list
 */
list_t *append_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_setting((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _duplicator(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * append_thenode_end - a node must be added to the end of the list
 *
 * @head: you should assign the pointer to the head node
 * @str: indicates to the sequence of characters assigned,
 * to field of node refered as str
 * @num: the number indicates to history's node index node
 *
 * Return: return when find the size of the list
 */
list_t *append_thenode_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_setting((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _duplicator(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * echo_thelist_str - a list_t linked list is printed only with its str element
 *
 * @h: you should assign the pointer to the first node
 *
 * Return: return with the size of the list
 */
size_t echo_thelist_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_adds(h->str ? h->str : "(nil)");
		_adds("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * erase_thenode_at_index - A node at a particular index is eliminated
 *
 * @head: you should assign the pointer to the head node
 * @index: the location of the selected node you wish to eliminate
 *
 * Return: return with 1 when yo succeed, and with 0 when failure
 */
int erase_thenode_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * letgo_thelist - all the nodes of the list must be freed
 *
 * @head_ptr: you should assign the pointer to the head of the  node
 *
 * Return: no value void
 */
void letgo_thelist(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
