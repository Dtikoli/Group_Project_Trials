#include "monty.h"

/**
 * handle_sub - handles the sub instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_sub(stack_t **stack, unsigned int line_number)
{
	int sub = 0;
	stack_t *node = NULL;
	stack_t *node_0 = get_dnodeint_at_index(*stack, 0);
	stack_t *node_1 = get_dnodeint_at_index(*stack, 1);

	if (dlistint_len(*stack) < 2)
	{
		fprintf(stderr, FAILURE_SUB, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	sub = node_1->n - node_0->n;
	delete_dnodeint_at_index(stack, 0);
	delete_dnodeint_at_index(stack, 0);
	node = add_dnodeint(stack, sub);
	if (!node)
	{
		fprintf(stderr, FAILURE_MALLOC);
		free_content(1);
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_div - handles the div instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_div(stack_t **stack, unsigned int line_number)
{
	int div = 0;
	stack_t *node = NULL;
	stack_t *node_0 = get_dnodeint_at_index(*stack, 0);
	stack_t *node_1 = get_dnodeint_at_index(*stack, 1);

	if (dlistint_len(*stack) < 2)
	{
		fprintf(stderr, FAILURE_DIV, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	if (node_0->n == 0)
	{
		fprintf(stderr, ERROR_DIV, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	div = node_1->n / node_0->n;
	delete_dnodeint_at_index(stack, 0);
	delete_dnodeint_at_index(stack, 0);
	node = add_dnodeint(stack, div);
	if (!node)
	{
		fprintf(stderr, FAILURE_MALLOC);
		free_content(1);
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_mul - handles the mul instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_mul(stack_t **stack, unsigned int line_number)
{
	int mul = 0;
	stack_t *node = NULL;
	stack_t *node_0 = get_dnodeint_at_index(*stack, 0);
	stack_t *node_1 = get_dnodeint_at_index(*stack, 1);

	if (dlistint_len(*stack) < 2)
	{
		fprintf(stderr, FAILURE_MUL, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	mul = node_1->n * node_0->n;
	delete_dnodeint_at_index(stack, 0);
	delete_dnodeint_at_index(stack, 0);
	node = add_dnodeint(stack, mul);
	if (!node)
	{
		fprintf(stderr, FAILURE_MALLOC);
		free_content(1);
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_mod - handles the mod instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_mod(stack_t **stack, unsigned int line_number)
{
	int mod = 0;
	stack_t *node = NULL;
	stack_t *node_0 = get_dnodeint_at_index(*stack, 0);
	stack_t *node_1 = get_dnodeint_at_index(*stack, 1);

	if (dlistint_len(*stack) < 2)
	{
		fprintf(stderr, FAILURE_MOD, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	if (node_0->n == 0)
	{
		fprintf(stderr, ERROR_DIV, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	mod = node_1->n % node_0->n;
	delete_dnodeint_at_index(stack, 0);
	delete_dnodeint_at_index(stack, 0);
	node = add_dnodeint(stack, mod);
	if (!node)
	{
		fprintf(stderr, FAILURE_MALLOC);
		free_content(1);
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_swap - handles the swap instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void handle_swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack, *node = NULL;
	int num;

	if (dlistint_len(*stack) < 2)
	{
		fprintf(stderr, FAILURE_SWAP, line_number);
		free_content(1);
		exit(EXIT_FAILURE);
	}

	temp = get_dnodeint_at_index(*stack, 0);
	num = temp->n;
	delete_dnodeint_at_index(stack, 0);
	node = insert_dnodeint_at_index(stack, 1, num);
	if (!node)
	{
		fprintf(stderr, FAILURE_MALLOC);
		free_content(1);
		exit(EXIT_FAILURE);
	}
}
