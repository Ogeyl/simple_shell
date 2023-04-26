#include "shell.h"
/**
 * add_node_end - adds a new node at the end of a list
 * @head: pointer to the head of the list
 * @str: string to add to the new node
 * @len: length of the string
 *
 * Return: pointer to the new node, or NULL if it fails
 */
list_t *add_node_end(list_t **head, char *str, size_t len)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);
	new_node->str = strdup(str);
	if (len == 0)
		len = strlen(str);
	new_node->len = len;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		list_t *last_node = *head;

		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (new_node);
}
