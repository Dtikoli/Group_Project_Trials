#include "main.h"

/**
 * print_c - Converts an argument to an unsigned char and
 *           stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_c(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	char c;
	unsigned int ret = 0;

	(void)prec;
	(void)len;

	c = va_arg(list, int);

	ret += numwidth_modify(output, ret, flags, width);
	ret += _memcpy(output, &c, 1);
	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

/**
 * print_s - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_s(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(list, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += strwidth_modify(output, flags, width, prec, size);

	prec = (prec == -1) ? size : prec;
	while (*str != '\0' && prec > 0)
	{
		ret += _memcpy(output, str, 1);
		prec--;
		str++;
	}

	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

/**
 * print_ns - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @list: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_ns(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	char *str, *null = "(null)", *nonprint = "\\x", zero = '0';
	int size, index;
	unsigned int ret = 0;

	(void)len;
	str = va_arg(list, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; str[size];)
		size++;

	ret += strwidth_modify(output, flags, width, prec, size);

	prec = (prec == -1) ? size : prec;
	for (index = 0; *(str + index) != '\0' && index < prec; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			ret += _memcpy(output, nonprint, 2);
			if (*(str + index) < 16)
				ret += _memcpy(output, &zero, 1);
			ret += ub_convert(output, *(str + index),
					     "0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		ret += _memcpy(output, (str + index), 1);
	}

	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

/**
 * print_r - Reverses a string and stores it
 *             to a buffer contained in a struct.
 * @list: A va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_r(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int size, end, i;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(list, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += strwidth_modify(output, flags, width, prec, size);

	end = size - 1;
	prec = (prec == -1) ? size : prec;
	for (i = 0; end >= 0 && i < prec; i++)
	{
		ret += _memcpy(output, (str + end), 1);
		end--;
	}

	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

/**
 * print_R - Converts a string to ROT13 and stores
 *             it to a buffer contained in a struct.
 * @list: A va_list pointing to the string to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @len: A lenth modifier.
 * @output: A buffer_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_R(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len)
{
	char *encode = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *decode = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, size;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(list, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	ret += strwidth_modify(output, flags, width, prec, size);

	prec = (prec == -1) ? size : prec;
	for (i = 0; str[i] && i < prec; i++)
	{
		for (j = 0; j < 52 && str[i] != encode[j]; j++)
			;

		if (str[i] == encode[j])
		{
			ret += _memcpy(output, &decode[j], 1);
		}
		if (j == 52)
			ret += _memcpy(output, (str + i), 1);
	}

	ret += negflag_width_modify(output, ret, flags, width);

	return (ret);
}

