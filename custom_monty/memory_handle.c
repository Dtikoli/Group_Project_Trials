#include "monty.h"

/**
 * free_handle - memory handling and FILE ptr closure function
 * @flag: gives indication of the content to free
 */
void free_handle(int flag)
{
	if (info.line)
	{
		free(info.line);
		info.line = NULL;
		free_str(info.words);
		info.words = NULL;
	}

	if (flag)
	{
		if (info.stack)
		{
			free_dlistint(info.stack);
			info.stack = NULL;
		}
		if (info.fp)
		{
			fclose(info.fp);
			info.fp = NULL;
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
