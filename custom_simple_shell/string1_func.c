#include "main.h"

/**
  * _strdup - returns a pointer to a new string
  * which is a duplicate of the string str
  * @str: a pointer to a string
  * Return: a pointer to a duplicate string,
  * NULL if str == NULL.
  */
char *_strdup(const char *str)
{
	char *p;
	int i, j;

	if (str == NULL)
		return (NULL);
	for (j = 0; str[j]; j++)
		;
	p = malloc(sizeof(*p) * (j + 1));
	if (p == NULL)
		return (NULL);
	for (i = 0; str[i]; i++)
		p[i] = str[i];
	return (p);
}

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @str: the source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *str)
{
	int i = 0;

	if (dest == str || str == 0)
		return (dest);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * **strtowk - splits a string into words. Ignores repeated delimiters
 * @str: input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtowk(char *str, char *del)
{
	int i, j, k, m, words = 0;
	char **ptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_is_delim(str[i], del) && (_is_delim(str[i + 1], del) || !str[i + 1]))
			words++;
	if (words == 0)
		return (NULL);
	ptr = malloc((1 + words) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (_is_delim(str[i], del))
			i++;
		k = 0;
		while (!_is_delim(str[i + k], del) && str[i + k])
			k++;
		ptr[j] = malloc((k + 1) * sizeof(char));
		if (ptr[j] == NULL)
		{
			for (k = 0; k < j; k++)
				free(ptr[k]);
			free(ptr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ptr[j][m] = str[i++];
		ptr[j][m] = '\0';
	}
	ptr[j] = NULL;
	return (ptr);
}

/**
 * **_strtow - splits a string into words
 * @str: input string
 * @delim: delimeter char
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_strtow(char *str, char delim)
{
	int i, j, k, m, words = 0;
	char **ptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			words++;
	if (words == 0)
		return (NULL);
	ptr = malloc((1 + words) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		ptr[j] = malloc((k + 1) * sizeof(char));
		if (ptr[j] == NULL)
		{
			for (k = 0; k < j; k++)
				free(ptr[k]);
			free(ptr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ptr[j][m] = str[i++];
		ptr[j][m] = '\0';
	}
	ptr[j] = NULL;
	return (ptr);
}
