#include "main.h"

/**
 * add_node - adds a node at the beginning of a linked list
 * @head: head pointer of linked list
 * @str: string field of node
 * @num: node index
 * Return: a pointer to the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: head pointer of linked list
 * @str: string field of node
 * @num: node index
 * Return: a pointer to the new element
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new, *tmp;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	tmp = *head;

	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*head = new;
	return (new);
}

/**
 * print_list_str - prints the string elements of a linked list
 * @head: linked list
 * Return: number of nodes
 */
size_t print_list_str(const list_t *head)
{
	size_t len = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		len++;
	}
	return (len);
}

/**
 * delete_node_index - deletes a node at a specified index
 * @head: head pointer of linked list
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node_index(list_t **head, unsigned int index)
{
	list_t *tmp, *prev;
	unsigned int c = 0;

	if (head == NULL || *head == NULL)
		return (0);

	tmp = *head;
	if (index == 0)
	{
		*head = (*head)->next;
		free(tmp->str);
		free(tmp);
		return (1);
	}

	while (tmp)
	{
		if (c == index)
		{
			prev->next = tmp->next;
			free(tmp->str);
			free(tmp);
			return (1);
		}
		c++;
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

/**
 * free_list - frees a linked list
 * @head: head pointer of linked list
 * Return: Nothing
 */
void free_list(list_t **head)
{
	list_t *tmp;

	if (head == NULL)
		return;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->str);
		free(tmp);
	}
}

