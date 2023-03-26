#include "main.h"

/**
 * print_hex - Converts an unsigned int argument to hex using abcdef
 *             and stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_hex(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char *lead = "0x";

	if (len == LONG)
		num = va_arg(list, unsigned long int);
	else
		num = va_arg(list, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		ret += ub_convert(output, num, "0123456789abcdef",
				flags, width, prec);

	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

/**
 * print_HEX - Converts an unsigned int argument to hex using ABCDEF
 *             and stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_HEX(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char *lead = "0X";

	if (len == LONG)
		num = va_arg(list, unsigned long);
	else
		num = va_arg(list, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		ret += ub_convert(output, num, "0123456789ABCDEF",
				flags, width, prec);

	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

/**
 * print_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int print_percent(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	char percent = '%';
	unsigned int ret = 0;

	(void)list;
	(void)prec;
	(void)len;

	ret += numwidth_modify(output, ret, flags, width);
	ret += _memcpy(output, &percent, 1);
	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

/**
 * print_add - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_add(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int ret = 0;

	(void)len;

	address = va_arg(list, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	ret += ub_convert(output, address, "0123456789abcdef",
			flags, width, prec);
	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

