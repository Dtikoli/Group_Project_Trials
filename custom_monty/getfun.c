#include "monty.h"

/**
 * get_func - selects the right function
 * @code: line from the bytecode file passed to main
 *
 * Return: pointer to the selected function, or NULL on failure
 */
void (*get_func(char **code))(stack_t **, unsigned int)
{
	instruction_t func[] = {
		{"push", handle_push},
		{"pall", handle_pall},
		{"pint", handle_pint},
		{"pop", handle_pop},
		{"swap", handle_swap},
		{"add", handle_add},
		{"nop", handle_nop},
		{"sub", handle_sub},
		{"div", handle_div},
		{"mul", handle_mul},
		{"mod", handle_mod},
		{"pchar", handle_pchar},
		{"pstr", handle_pstr},
		{"rotl", handle_rotl},
		{"rotr", handle_rotr},
		{"stack", handle_stack},
		{"queue", handle_queue},
		{NULL, NULL}
	};

	int i, num = 17;

	for (i = 0; i < num; i++)
	{
		if (strcmp(func[i].opcode, code[0]) == 0)
		{
			return (func[i].f);
		}
	}
	return (NULL);
}
