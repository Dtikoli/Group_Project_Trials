#include "monty.h"

/**
 * free_content - memory handling and FILE ptr closure function
 * @f: gives indication of the content to free
 */
void free_content(int f)
{
	if (content.line)
	{
		free(content.line);
		content.line = NULL;
		free_array(content.words);
		content.words = NULL;
	}

	if (f)
	{
		if (content.stack)
		{
			free_dlistint(content.stack);
			content.stack = NULL;
		}
		if (content.fp)
		{
			fclose(content.fp);
			content.fp = NULL;
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
