#include "main.h"

/**
 * _printf - formated output conversion and print data.
 * @format: input string.
 * Return: number of chars printed.
 */
int _printf(const char *format, ...)
{
	int i, pr = 0, pr_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				buff_handle(buffer, &buff_ind);
			pr_chars++;
		}
		else
		{
			buff_handle(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			pr = write_handle(format, &i, list, buffer,
					flags, width, precision, size);
			if (pr == -1)
				return (-1);
			pr_chars += pr;
		}
	}
	buff_handle(buffer, &buff_ind);
	va_end(list);
	return (pr_chars);
}

/**
 * buff_handle - prints the contents of the buffer is it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length
 */
void buff_handle(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}
