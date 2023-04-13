#include "main.h"

/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, num;
	unsigned int ret = 0;

	for (i = 0;  str[i] && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			ret *= 10;
			ret += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		num = -ret;
	else
		num = ret;

	return (num);
}

/**
 * _print_decimal - prints an integer
 * @input: integer
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */
int _print_decimal(int input, int fd)
{
	int (*_put_char)(char) = _putchar;
	int i, ret = 0;
	unsigned int _abs_, cur;

	if (fd == STDERR_FILENO)
		_put_char = _err_putc;
	if (input < 0)
	{
		_abs_ = -input;
		_put_char('-');
		ret++;
	}
	else
		_abs_ = input;
	cur = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_put_char('0' + cur / i);

			ret++;
		}
		cur %= i;
	}
	_put_char('0' + cur);
	ret++;

	return (ret);
}

/**
 * convert_num - base converter function
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_num(long int num, int base, int flags)
{
	static char *str;
	static char buff[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	str = flags & CONVERT_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = str[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _remove_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 * Return: Always 0
 */
void _remove_comments(char *buff)
{
	int i;

	for (i = 0; buff[i]; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}

