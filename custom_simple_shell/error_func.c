#include "main.h"

/**
 * print_error - controls printing of error messages
 * @info: struct containing potential arguments
 * @estr: string containing error type
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 *_eputs - for printing error string
 * @str: string to be printed
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - for writing error chars
 * @c: char to be print
 * Return: On success 1, on error, -1.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= BUFF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - for writing chars to a specified fd
 * @c: char to print
 * @fd: file descriptor
 * Return: On success 1, on error, -1.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= BUFF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - for printing a string to a given fd
 * @str: string to be printed
 * @fd: file descriptor
 * Return: number of printed chars
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
