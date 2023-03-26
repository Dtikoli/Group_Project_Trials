#include "main.h"

/**
 * print_di - Converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_di(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	long int d, copy;
	unsigned int ret = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	d = (len == LONG) ? va_arg(list, long int) : va_arg(list, int);
	if (len == SHORT)
		d = (short)d;
	if (SPACE_FLAG == 1 && d >= 0)
		ret += _memcpy(output, &space, 1);
	if (prec <= 0 && NEG_FLAG == 0)
	{
		if (d == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		}
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			ret += _memcpy(output, &plus, 1);
		if (ZERO_FLAG == 1 && d < 0)
			ret += _memcpy(output, &neg, 1);
		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (width -= count; width > 0; width--)
			ret += _memcpy(output, &pad, 1);
	}
	if (ZERO_FLAG == 0 && d < 0)
		ret += _memcpy(output, &neg, 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		ret += _memcpy(output, &plus, 1);
	if (!(d == 0 && prec == 0))
		ret += sb_convert(output, d, "0123456789", flags, 0, prec);
	ret += negflag_width_modify(output, ret, flags, width);
	return (ret);
}

/**
 * print_b - Converts an unsigned int argument to binary
 *             and stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_b(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	unsigned int num;

	num = va_arg(list, unsigned int);

	(void)len;

	return (ub_convert(output, num, "01", flags, width, prec));
}

/**
 * print_o - Converts an unsigned int to octal and
 *             stores it to a buffer contained in a struct.
 * @list: A va_list poinitng to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_o(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;
	char zero = '0';

	if (len == LONG)
		num = va_arg(list, unsigned long int);
	else
		num = va_arg(list, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		ret += _memcpy(output, &zero, 1);

	if (!(num == 0 && prec == 0))
		ret += ub_convert(output, num, "01234567",
				flags, width, prec);

	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

/**
 * print_u - Converts an unsigned int argument to decimal and
 *               stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_u(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int ret = 0;

	if (len == LONG)
		num = va_arg(list, unsigned long int);
	else
		num = va_arg(list, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (!(num == 0 && prec == 0))
		ret += ub_convert(output, num, "0123456789",
				flags, width, prec);

	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}
