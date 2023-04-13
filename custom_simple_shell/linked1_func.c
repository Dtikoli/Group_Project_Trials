#include "main.h"

/**
 * list_len - determines the number of elements in a linked list
 * @head: linked list
 * Return: number of nodes
 */
size_t list_len(const list_t *head)
{
	size_t len = 0;

	while (head)
	{
		head = head->next;
		len++;
	}
	return (len);
}

/**
 * list_to_strings - returns an array of strings of the list
 * @h: linked list
 * Return: array of strings
 */
char **list_to_strings(list_t *h)
{
	list_t *node = h;
	size_t len, i, j;
	char **s;
	char *str;

	len = list_len(h);
	if (!h || !len)
		return (NULL);
	s = malloc(sizeof(char *) * (len + 1));
	if (s == NULL)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (str == NULL)
		{
			for (j = 0; j < i; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		s[i] = str;
	}
	s[i] = NULL;
	return (s);
}


/**
 * print_list - prints elements of a linked list
 * @head: linked list
 * Return: number of nodes
 */
size_t print_list(const list_t *head)
{
	size_t len = 0;

	while (head)
	{
		_puts(convert_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		len++;
	}
	return (len);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @head: linked list
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: matched node or null
 */
list_t *node_starts_with(list_t *head, char *prefix, char c)
{
	char *ptr = NULL;
	list_t *node = head;

	while (node)
	{
		ptr = _starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @h: linked list
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *h, list_t *node)
{
	size_t j = 0;

	while (h)
	{
		if (h == node)
			return (j);
		h = h->next;
		j++;
	}
	return (-1);
}

