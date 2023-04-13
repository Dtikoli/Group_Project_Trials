#include "main.h"

/**
 *_puts - prints an input string
 *@str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the chars to STDOUT
 * @c: char to print
 * Return: On success 1, on error, -1.
 */
int _putchar(char c)
{
	static int len;
	static char buff[BUFF_SIZE];

	if (c == BUF_FLUSH || len >= BUFF_SIZE)
	{
		write(STDOUT_FILENO, buff, len);
		len = 0;
	}
	if (c != BUF_FLUSH)
		buff[len++] = c;
	return (1);
}

/**
 * _interact - checks shell's interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int _interact(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _is_delim - checks a delimiter character
 * @c: char to check
 * @delim: delimeter string
 * Return: 1 if true, 0 if false
 */
int _is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: char to input
 *Return: 1 if c is an alphabet, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

