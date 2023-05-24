#include "monty.h"

info_t info = INFO_INIT;

/**
  * errorusage_print - prints error messeages upon usage failure
  * Return: Nothing
  */
void errorusage_print(void)
{
	fprintf(stderr, ERROR_USAGE);
	exit(EXIT_FAILURE);
}


/**
  * errormalloc_print - prints error messeages if malloc fails
  * Return: Nothing
  */
void errormalloc_print(void)
{
	fprintf(stderr, FAILURE_MALLOC);
	exit(EXIT_FAILURE);
}

/**
 * parse_monty - helper function for main function
 * @clargs: pointer to struct of arguments from main
 *
 * Description: opens and reads from the file
 * containing the opcodes, and calls the function
 * that will find the corresponding executing function
 */
void parse_monty(cmd_t *clargs)
{
	char *_gets = NULL;
	void (*opcode_func)(stack_t **, unsigned int);

	if (clargs->ac != 2)
		errorusage_print();
	info.fp = fopen(clargs->av, "r");
	if (!info.fp)
	{
		fprintf(stderr, ERROR_FILE, clargs->av);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		clargs->nline++;
		info.line = malloc(1024);
		if (!info.line)
			errormalloc_print();
		_gets = fgets(info.line, 1024, info.fp);
		if (!_gets)
			break;
		info.words = strtow(info.line);
		if (info.words[0] == NULL || info.words[0][0] == '#')
		{
			free_handle(0);
			continue;
		}
		opcode_func = get_func(info.words);
		if (!opcode_func)
		{
			fprintf(stderr, ERROR_UNKNOWN, clargs->nline, info.words[0]);
			free_handle(1);
			exit(EXIT_FAILURE);
		}
		opcode_func(&(info.stack), clargs->nline);
		free_handle(0);
	}
	free_handle(1);
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
	cmd_t clargs;

	clargs.av = argv[1];
	clargs.ac = argc;
	clargs.nline = 0;

	parse_monty(&clargs);

	return (EXIT_SUCCESS);
}
