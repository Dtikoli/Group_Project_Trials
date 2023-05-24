#include "monty.h"
#include "lists.h"

data_t data = DATA_INIT;

/**
 * monty - helper function for main function
 * @args: pointer to struct of arguments from main
 *
 * Description: opens and reads from the file
 * containing the opcodes, and calls the function
 * that will find the corresponding executing function
 */
void monty(args_t *args)
{
	char *_gets = NULL;
	void (*code_func)(stack_t **, unsigned int);

	if (args->ac != 2)
	{
		fprintf(stderr, ERROR_USAGE);
		exit(EXIT_FAILURE);
	}
	data.fptr = fopen(args->av, "r");
	if (!data.fptr)
	{
		fprintf(stderr, ERROR_FILE, args->av);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		args->line_number++;
		data.line = malloc(1024);
		if (!data.line)
		{
			fprintf(stderr, FAILURE_MALLOC);
			exit(EXIT_FAILURE);
		}
		_gets = fgets(data.line, 1024, data.fptr);
		if (!_gets)
			break;
		data.words = strtow(data.line);
		if (data.words[0] == NULL || data.words[0][0] == '#')
		{
			free_all(0);
			continue;
		}
		code_func = get_func(data.words);
		if (!code_func)
		{
			fprintf(stderr, ERROR_UNKNOWN, args->line_number, data.words[0]);
			free_all(1);
			exit(EXIT_FAILURE);
		}
		code_func(&(data.stack), args->line_number);
		free_all(0);
	}
	free_all(1);
}

/**
 * main - entry point for monty bytecode interpreter
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	args_t args;

	args.av = argv[1];
	args.ac = argc;
	args.line_number = 0;

	monty(&args);

	return (EXIT_SUCCESS);
}