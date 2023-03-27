#include "main.h"

/**
 * numwidth_modify - Stores leading spaces to a buffer for a width modifier.
 * @output: A buffer_t struct containing a character array.
 * @printed: The current number of characters already printed to output
 *           for a given number specifier.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int numwidth_modify(buffer_t *output, unsigned int printed,
		unsigned char flags, int width)
{
	unsigned int ret = 0;
	char w_width = ' ';

	if (NEG_FLAG == 0)
	{
		for (width -= printed; width > 0;)
			ret += _memcpy(output, &w_width, 1);
	}

	return (ret);
}

/**
 * strwidth_modify - Stores leading spaces to a buffer for a width modifier.
 * @output: A buffer_t struct containing a character array.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @size: The size of the string.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int strwidth_modify(buffer_t *output,
		unsigned char flags, int width, int prec, int size)
{
	unsigned int ret = 0;
	char w_width = ' ';

	if (NEG_FLAG == 0)
	{
		width -= (prec == -1) ? size : prec;
		for (; width > 0; width--)
			ret += _memcpy(output, &w_width, 1);
	}

	return (ret);
}

/**
 * negflag_width_modify - Stores trailing spaces to a buffer for a '-' flag.
 * @output: A buffer_t struct containing a character array.
 * @printed: The current number of bytes already stored to output
 *           for a given specifier.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int negflag_width_modify(buffer_t *output, unsigned int printed,
		unsigned char flags, int width)
{
	unsigned int ret = 0;
	char w_width = ' ';

	if (NEG_FLAG == 1)
	{
		for (width -= printed; width > 0; width--)
			ret += _memcpy(output, &w_width, 1);
	}

	return (ret);
}

