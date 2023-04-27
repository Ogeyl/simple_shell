#include "shell.h"

/**
* _memset - fills memory with a constant byte
* @s: the pointer to the memory area
* @b: the byte to fill *s with
* @n: the amount of bytes to be filled
* Return: (s) a pointer to the memory area s
*/
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
* ffree - frees a string of strings
* @pp: string of strings
*/
void ffree(char **pp)
{
	if (pp == NULL)
	{
		return;
	}
	free(pp);
}

/**
* _realloc - reallocates a block of memory
* @ptr: pointer to previous malloc'ated block
* @old_size: byte size of previous block
* @new_size: byte size of new block
*
* Return: pointer to da ol'block nameen.
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
	{
	/* ptr is NULL, treat as malloc */
	new_ptr = malloc(new_size);
		if (new_ptr == NULL)
		{
		return (NULL);
	}
	return (new_ptr);
	}
	else if (new_size == 0)
	{
	/* new_size is 0, treat as free */
	free(ptr);
	return (NULL);
	}
	else if (new_size <= old_size)
	{
	/* new_size is less than or equal to old_size, return ptr */
	return (ptr);
	}
	else
	{
	/* new_size is greater than old_size, realloc */
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		{
		return (NULL);
	}
	memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
	}
}
