#include "monty.h"
#include "lists.h"

/**
 * free_handle - memory handling and FILE ptr closure function
 * @flag: gives indication of the content to free
 */
void free_handle(int flag)
{
	if (data.line)
	{
		free(data.line);
		data.line = NULL;
		free_str(data.words);
		data.words = NULL;
	}

	if (flag)
	{
		if (data.stack)
		{
			free_dlistint(data.stack);
			data.stack = NULL;
		}
		if (data.fptr)
		{
			fclose(data.fptr);
			data.fptr = NULL;
		}
	}
}


/**
 * free_str - frees arrays of strings
 * @args: array of strings to free
 */
void free_str(char **args)
{
	int j;

	if (!args)
		return;

	for (j = 0; args[j]; j++)
		free(args[j]);

	free(args);
}
