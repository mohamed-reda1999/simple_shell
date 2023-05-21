#include "shell.h"

/**
 * bfree - NULLs the address after a pointer is released
 *
 * @ptr: The memory location of the pointer that needs to be freed
 *
 * Return: The resulting value will be 1 if the input is released,
 * and 0 otherwise
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
