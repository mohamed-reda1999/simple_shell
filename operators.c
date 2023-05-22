#include "shell.h"

/**
 * _memset - a constant byte is filled into memory
 * @s: the pointer located in the memory region
 *
 * @b: indicates to the byte that is utilized to fill *s
 * @n: the numbers of bytes that needs to be filled
 *
 * Return: return with (s)which is a pointer to the memory location s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - A string of strings is released
 *
 * @pp: refers to one string of the strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - a block of a memory needs to be relocated
 * @ptr: Pointer to a block that was previously malloc'd
 * @old_size: size of the previous block of byte
 *
 * @new_size: the byte size of the block that has been created
 * Return: return with the output thatat refers to the pointer,
 * the new block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
