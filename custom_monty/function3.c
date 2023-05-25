#include "monty.h"

/**
 * _nop - handles the nop instruction
 * @stack: double pointer to the stack to push to
 * @nline: number of the line in the file
 */
void _nop(stack_t **stack, unsigned int nline)
{
	(void)stack;
	(void)nline;
}

/**
 * _rotl - handles the rotl instruction
 * @stack: double pointer to the stack to push to
 * @nline: number of the line in the file
 */
void _rotl(stack_t **stack, unsigned int nline)
{
	stack_t *temp = *stack;
	int num  = 0;

	(void)nline;

	if (*stack == NULL)
		return;
	temp = get_dnodeint_at_index(*stack, 0);
	num = temp->n;
	delete_dnodeint_at_index(stack, 0);
	add_dnodeint_end(stack, num);
}

/**
 * _rotr - handles the rotr instruction
 * @stack: double pointer to the stack to push to
 * @nline: number of the line in the file
 */
void _rotr(stack_t **stack, unsigned int nline)
{
	stack_t *temp = *stack;
	int num = 0, len = dlistint_len(*stack);

	(void)nline;

	if (*stack == NULL)
		return;
	temp = get_dnodeint_at_index(*stack, len - 1);
	num = temp->n;
	delete_dnodeint_at_index(stack, len - 1);
	add_dnodeint(stack, num);
}

/**
 * _stack - handles the stack instruction
 * @stack: double pointer to the stack to push to
 * @nline: number of the line in the file
 */
void _stack(stack_t **stack, unsigned int nline)
{
	(void)stack;
	(void)nline;
	info.sflag = 0;
}


/**
 * _queue - handles the queue instruction
 * @stack: double pointer to the stack to push to
 * @nline: number of the line in the file
 */
void _queue(stack_t **stack, unsigned int nline)
{
	(void)stack;
	(void)nline;
	info.sflag = 1;
}
