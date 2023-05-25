#include "monty.h"

/**
 * handle_push - handles the push instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_push(stack_t **stack, unsigned int line_number)
{
	stack_t *new;
	int num = 0, i;

	if (info.words[1] == NULL)
	{
		fprintf(stderr, FAILURE_PUSH, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	for (i = 0; info.words[1][i]; i++)
	{
		if (isalpha(info.words[1][i]) != 0)
		{
			fprintf(stderr, FAILURE_PUSH, line_number);
			free_content(1);
			exit(EXIT_FAILURE);
		}
	}
	num = atoi(info.words[1]);

	if (info.sflag == 0)
		new = add_dnodeint(stack, num);
	else if (info.sflag == 1)
		new = add_dnodeint_end(stack, num);
	if (!new)
	{
		fprintf(stderr, FAILURE_MALLOC);
		free_content(1);
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_pall - handles the pall instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_pall(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	if (*stack)
		print_dlistint(*stack);
}

/**
 * handle_pint - handles the pint instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_pint(stack_t **stack, unsigned int line_number)
{
	stack_t *head = *stack;

	if (!head)
	{
		fprintf(stderr, FAILURE_PINT, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", head->n);
}

/**
 * handle_pop - handles the pop instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	if (!temp)
	{
		fprintf(stderr, FAILURE_POP, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	delete_dnodeint_at_index(stack, 0);
}

/**
 * handle_add - handles the add instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_add(stack_t **stack, unsigned int line_number)
{
	int sum = 0;
	stack_t *node = NULL;
	stack_t *node_0 = get_dnodeint_at_index(*stack, 0);
	stack_t *node_1 = get_dnodeint_at_index(*stack, 1);

	if (dlistint_len(*stack) < 2)
	{
		fprintf(stderr, FAILURE_ADD, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	sum = node_0->n + node_1->n;
	delete_dnodeint_at_index(stack, 0);
	delete_dnodeint_at_index(stack, 0);
	node = add_dnodeint(stack, sum);
	if (!node)
	{
		fprintf(stderr, FAILURE_MALLOC);
		free_content(1);
		exit(EXIT_FAILURE);
	}
}
