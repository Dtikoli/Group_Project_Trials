#include "main.h"

/**
 * _strlen - return the length of the string
 * @s: char type pointer
 * Return: length of string
 */
int _strlen(char *s)
{
	int ch;

	for (ch = 0; s[ch]; ch++)
		;

	return (ch);
}

/**
 * _strcmp - Compare two strings
 * @s1: string
 * @s2: string
 * Return: negative int if s1 < s2, 0 if matching, and positive int if s1 > s2
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++)
		;
	return (s1[i] - s2[i]);
}

/**
 **_strncpy - copies a string
 *@dest: destination string
 *@str: source string
 *@n: number of chars to be copied
 *Return: a pointer to the destination string
 */
char *_strncpy(char *dest, char *str, int n)
{
	int i;

	for (i = 0; str[i] && i < n; i++)
		dest[i] = str[i];
	for ( ; i < n; i++)
		dest[i] = '\0';
	return (dest);
}

/**
 **_strncat - concatenates two strings
 *@dest: destination string
 *@src: source string
 *@n: number of bytes to be used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;

	for (i = 0; dest[i]; i++)
		;
	for (j = 0; src[j] && j < n; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return (dest);
}

/**
 * _strchr - locate 1st occurrence of char in string and returns pointer there
 * @s: string to search
 * @c: target characer
 * Return: pointer to that character in string
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	for (; s[i] && s[i] != c; i++) /* find match */
		;
	if (s[i] == c) /* if match, assign to address */
		return (s + i);
	else
		return (0);
}
