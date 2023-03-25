#include "main.h"
/**
 * write_handle - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @index: buffer index
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int write_handle(const char *format, int *index, va_list list, char buffer[],
			int flags, int width, int precision, int size)
{
	int i, un_len = 0, pr_chars = -1;
	_fprint formats[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', '\0'}
	};

	for (i = 0; formats[i].opts != '\0'; i++)
		if (format[*index] == formats[i].opts)
			return (formats[i].fn(list, buffer, flags, width, precision, size));
	if (formats[i].opts == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		un_len += write(1, "%%", 1);
		if (format[*index - 1] == ' ')
			un_len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		un_len += write(1, &format[*index], 1);
		return (un_len);
	}
	return (pr_chars);
}

