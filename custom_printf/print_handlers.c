#include "main.h"

/**
 * write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int write_char(char c, char buffer[],
			int flags, int width, int precision, int size)
{
	int i = 0;
	char pad = ' ';

	(void) precision;
	(void) size;
	if (flags & F_ZERO)
		pad = '0';
	buffer[i++] = c;
	buffer[i] = '\0';
	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = pad;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}
/**
 * write_number - Prints all numbers
 * @is_negative: Lista of arguments
 * @index: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int index, char buffer[],
			int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char pad = ' ', add_ch = 0;

	(void) size;
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		add_ch = '-';
	else if (flags & F_PLUS)
		add_ch = '+';
	else if (flags & F_SPACE)
		add_ch = ' ';
	return (write_num(index, buffer, flags, width, precision,
				length, pad, add_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @pad: Pading char
 * @add_c: Extra char
 * Return: Number of printed chars.
 */
int write_num(int index, char buffer[],
			int flags, int width, int prec,
				int length, char pad, char add_c)
{
	int i, pad_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0);
	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = pad = ' ';
	if (prec > 0 && prec < length)
		pad = ' ';
	while (prec > length)
		buffer[--index] = '0', length++;
	if (add_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flags & F_MINUS && pad == ' ')
		{
			if (add_c)
				buffer[--index] = add_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && pad == ' ')
		{
			if (add_c)
				buffer[--index] = add_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (add_c)
				buffer[--pad_start] = add_c;
			return (write(1, &buffer[pad_start], i - pad_start) +
					write(1, &buffer[index], length - (1 - pad_start)));
		}
	}
	if (add_c)
		buffer[--index] = add_c;
	return (write(1, &buffer[index], length));
}

/**
 * write_unsgned - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of written chars.
 */
int write_unsgned(int is_negative, int index,
			char buffer[],
				int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, i = 0;
	char pad = ' ';

	(void) is_negative;
	(void) size;
	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);
	if (precision > 0 && precision < length)
		pad = ' ';
	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flags & F_MINUS)
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		else
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
	}
	return (write(1, &buffer[index], length));
}

/**
 * write_add - Write a memory address
 * @buffer: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @pad: Char representing the padding
 * @add_c: Char representing extra char
 * @pad_start: Index at which padding should start
 * Return: Number of written chars.
 */
int write_add(char buffer[], int index, int length,
			int width, int flags, char pad, char add_c, int pad_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flags & F_MINUS && pad == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (add_c)
				buffer[--index] = add_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && pad == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (add_c)
				buffer[--index] = add_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')
		{
			if (add_c)
				buffer[--pad_start] = add_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[pad_start], i - pad_start) +
					write(1, &buffer[index], length - (1 - pad_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (add_c)
		buffer[--index] = add_c;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}

