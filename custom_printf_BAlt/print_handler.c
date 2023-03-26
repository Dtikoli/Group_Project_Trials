#include "main.h"

/**
 * print_handle - Reads through the format string for _printf.
 * @format: Character string to print - may contain directives.
 * @output: A buffer_t struct containing a buffer.
 * @list: A va_list of arguments.
 * Return: The number of characters stored to output.
 */
int print_handle(const char *format, va_list list, buffer_t *output)
{
	int i, width, prec, ret = 0;
	char tmp;
	unsigned char flags, len;
	unsigned int (*funct)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		len = 0;
		if (*(format + i) == '%')
		{
			tmp = 0;
			flags = flag_handle(format + i + 1, &tmp);
			width = width_handle(list, format + i + tmp + 1, &tmp);
			prec = prec_handle(list, format + i + tmp + 1,
					&tmp);
			len = len_handle(format + i + tmp + 1, &tmp);

			funct = type_handle(format + i + tmp + 1);
			if (funct != NULL)
			{
				i += tmp + 1;
				ret += funct(list, output, flags, width, prec, len);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				ret = -1;
				break;
			}
		}
		ret += _memcpy(output, (format + i), 1);
		i += (len != 0) ? 1 : 0;
	}
	va_end(list);
	write(1, output->start, output->len);
	free_buffer(output);
	return (ret);
}

