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
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"add", _add},
		{"nop", _nop},
		{"sub", _sub},
		{"div", _div},
		{"mul", _mul},
		{"mod", _mod},
		{"pchar", _pchar},
		{"pstr", _pstr},
		{"rotl", _rotl},
		{"rotr", _rotr},
		{"stack", _stack},
		{"queue", _queue},
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
