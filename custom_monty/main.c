#include "monty.h"

mon_t content = CONTENT_INIT;

/**
  * errorusage_print - prints error messeages upon usage failure
  * Return: Nothing
  */
void errorusage_print(void)
{
	fprintf(stderr, ERR_USAGE);
	exit(EXIT_FAILURE);
}


/**
  * errormalloc_print - prints error messeages if malloc fails
  * Return: Nothing
  */
void errormalloc_print(void)
{
	fprintf(stderr, FAIL_MALLOC);
	exit(EXIT_FAILURE);
}

/**
 * monty - helper function for main function
 * @clargs: pointer to struct of arguments from main
 *
 * Description: opens and reads from the file
 * containing the opcodes, and calls the function
 * that will find the corresponding executing function
 */
void monty(cmd_t *clargs)
{
	char *line_gets = NULL;
	void (*opfunc)(stack_t **, unsigned int);

	if (clargs->ac != 2)
		errorusage_print();
	content.fp = fopen(clargs->av, "r");
	if (!content.fp)
	{
		fprintf(stderr, ERR_FILE, clargs->av);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		clargs->nline++;
		content.line = malloc(1024);
		if (!content.line)
			errormalloc_print();
		line_gets = fgets(content.line, 1024, content.fp);
		if (line_gets == NULL)
			break;
		content.words = strtow(content.line);
		if (content.words[0] == NULL || content.words[0][0] == '#')
		{
			free_content(0);
			continue;
		}
		opfunc = get_func(content.words);
		if (!opfunc)
		{
			fprintf(stderr, ERR_UNKNOWN, clargs->nline, content.words[0]);
			free_content(1);
			exit(EXIT_FAILURE);
		}
		opfunc(&(content.stack), clargs->nline);
		free_content(0);
	}
	free_content(1);
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

	monty(&clargs);

	return (EXIT_SUCCESS);
}
