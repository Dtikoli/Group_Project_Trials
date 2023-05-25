#include "monty.h"

/**
 * dlistint_len - returns the number of nodes in a doubly linked list
 * @h: pointer to the list
 *
 * Return: number of nodes
 */
size_t dlistint_len(const stack_t *h)
{
	size_t size = 0;

	if (!h)
		return (0);

	while (h)
	{
		size++;
		h = h->next;
	}

	return (size);
}

/**
 * add_dnodeint - adds a new node at the beginning of a doubly linked list
 * @head: double pointer to the list
 * @n: data to insert in the new node
 *
 * Return: the address of the new element, or NULL if it failed
 */
stack_t *add_dnodeint(stack_t **head, const int n)
{
	stack_t *new;

	if (!head)
		return (NULL);

	new = malloc(sizeof(stack_t));
	if (!new)
		return (NULL);

	new->n = n;

	new->next = *head;
	new->prev = NULL;

	if (*head)
		(*head)->prev = new;

	*head = new;

	return (new);
}

/**
 * print_dlistint - prints a doubly linked list
 * @h: pointer to the list
 *
 * Return: number of nodes in the list
 */
size_t print_dlistint(const stack_t *h)
{
	size_t size = 0;

	if (!h)
		return (0);

	while (h)
	{
		printf("%d\n", h->n);
		h = h->next;
		size++;
	}

	return (size);
}

/**
 * delete_dnodeint_at_index - deltes a node in a doubly linked list
 * at a given index
 * @head: double pointer to the list
 * @index: index of the node to delete
 *
 * Return: 1 on success, -1 on failure
 */
int delete_dnodeint_at_index(stack_t **head, unsigned int index)
{
	stack_t *temp = *head;
	unsigned int i = 0;

	if (!index)
	{
		(*head) = temp->next;
		if (temp->next)
			temp->next->prev = NULL;
		temp->next = NULL;
		free(temp);
		return (1);
	}

	while (i < index)
	{
		temp = temp->next;
		i++;
		if (!temp)
			return (0);
	}

	temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp);

	return (1);
}

/**
 * get_dnodeint_at_index - gets the nth node of a doubly linked list
 * @head: pointer to the list
 * @index: index of the node to return
 *
 * Return: address of the node, or if it does not exist, NULL
 */
stack_t *get_dnodeint_at_index(stack_t *head, unsigned int index)
{
	unsigned int idx = 0;

	if (!head)
		return (NULL);

	while (head && idx < index)
	{
		head = head->next;
		idx++;
	}

	return (head ? head : NULL);
}
