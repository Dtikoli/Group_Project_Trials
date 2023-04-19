#include "main.h"

/**
 * _strcmp - compares two strangs and check if they are same.
 * @s1: string 1
 * @s2: string 2
 * Return: 0 is strings are same, other a negative or postive integer.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 **_strncpy - copies a string
 *@dest: destination string
 *@src: source string
 *@n: number of bytes to copy
 *Return: a pointer to the destination string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: destination string
 *@src: source string
 *@n: number of bytes to concatenate
 *Return: a pointer to the destination string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a char in a string
 *@s: string to be parsed
 *@c: char to look for
 *Return: a pointer to the located char
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * _strstr - locates a substring
 * @haystack: string to be scanned
 * @needle: string containing the sequence of characters to match
 * Return: pointer to the beginning of the located substring, or NULL if the
*/
char *_strstr(char *haystack, char *needle)
{
	int i, j;

	for (i = 0; haystack[i]; i++)
	{
		for (j = 0; needle[j] && haystack[i + j]; j++)
			if (haystack[i + j] != needle[j])
				break;
		if (!needle[j])
			return (haystack + i);
	}
	return (NULL);
}
