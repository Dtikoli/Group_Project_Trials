#include "main.h"

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list list;
	int ret;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(list, format);

	ret = print_handle(format, list, output);

	return (ret);
}
