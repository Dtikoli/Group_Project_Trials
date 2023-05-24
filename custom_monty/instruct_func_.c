#include "monty.h"

/**
 * get_func - selects the right function
 * @opc: line from the bytecode file passed to main
 *
 * Return: pointer to the selected function, or NULL on failure
 */
void (*get_func(char **opc))(stack_t **, unsigned int)
{
	instruction_t opc_func[] = {
		{"push", push_handler},
		{"pall", pall_handler},
		{"pint", pint_handler},
		{"pop", pop_handler},
		{"swap", swap_handler},
		{"add", add_handler},
		{"nop", nop_handler},
		{"sub", sub_handler},
		{"div", div_handler},
		{"mul", mul_handler},
		{"mod", mod_handler},
		{"pchar", pchar_handler},
		{"pstr", pstr_handler},
		{"rotl", rotl_handler},
		{"rotr", rotr_handler},
		{"stack", stack_handler},
		{"queue", queue_handler},
		{NULL, NULL}
	};

	int i, n_opcs = 17;

	for (i = 0; i < n_opcs; i++)
	{
		if (strcmp(opc_func[i].opcode, opc[0]) == 0)
		{
			return (opc_func[i].f);
		}
	}
	return (NULL);
}
