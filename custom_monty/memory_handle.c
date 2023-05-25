#include "monty.h"

/**
 * free_content - memory handling and FILE ptr closure function
 * @f: gives indication of the content to free
 */
void free_content(int f)
{
	if (info.line)
	{
		free(info.line);
		info.line = NULL;
		free_array(info.words);
		info.words = NULL;
	}

	if (f)
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
 * free_array - frees arrays of strings
 * @args: array of strings to free
 */
void free_array(char **args)
{
	int j;

	if (!args)
		return;

	for (j = 0; args[j]; j++)
		free(args[j]);

	free(args);
}
