#include "shell.h"

/**
* list_len - determines length of linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		count++;
		h = h->next;
	}
	return (count);
}

/**
* list_to_strings - returns an array of strings of the list->str
* @head: pointer to first node
*
* Return: array of strings
*/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		strs[i] = _strdup(node->str);
	}
	strs[i] = NULL;
	return (strs);
}


/**
* print_list - prints all elements of a list_t linked list
* @h: pointer to first node
*
* Return: size of list
*/
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
* node_starts_with - returns node whose string starts with prefix
* @node: pointer to list head
* @prefix: string to match
* @c: the next character after prefix to match
*
* Return: match node or null
*/
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && (*p == c))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
* get_node_index - gets the index of a node
* @head: pointer to list head
* @node: pointer to the node
*
* Return: index of node or -1
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;
	list_t *current;
	for (list_t *current = head; current; current = current->next, index++)
		if (current == node)
			return (index);
	return (-1);
}
