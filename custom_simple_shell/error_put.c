#include "main.h"

/**
 *_err_puts - prints an error string to STDERR
 * @str: the string to be printed
 * Return: Nothing
 */
void _err_puts(char *str)
{
	int j;

	if (!str)
		return;
	for (j = 0; str[j]; j++)
		_err_putc(str[j]);
}

/**
 * _err_putc - write chars to stderr
 * @c: char to print
 * Return: On success 1, on error -1, and errno is set.
 */
int _err_putc(char c)
{
	static int j;
	static char buff[BUFF_SIZE];

	if (c == BUF_FLUSH || j >= BUFF_SIZE)
	{
		write(STDERR_FILENO, buff, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}


/**
 * _err_atoi - converts an error string to an integer
 * @str: string to be converted
 * Return: converted numbers, -1 on error
 */
int _err_atoi(char *str)
{
	int i;
	unsigned long int num = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i]; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num *= 10;
			num += (str[i] - '0');
			if (num > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (num);
}

/**
 * _print_err - prints an error message to STDERR
 * @info: return info struct
 * @estr: string containing specified error type
 * Return: Nothing
 */
void _print_err(info_t *info, char *estr)
{
	_err_puts(info->fname);
	_err_puts(": ");
	_print_decimal(info->line_count, STDERR_FILENO);
	_err_puts(": ");
	_err_puts(info->argv[0]);
	_err_puts(": ");
	_err_puts(estr);
}

