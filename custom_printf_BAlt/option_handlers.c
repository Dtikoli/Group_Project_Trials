#include "main.h"

/**
 * flag_handle - Matches flags with corresponding values.
 * @flag: A pointer to a potential string of flags.
 * @index: An index counter for the original format string.
 * Return: If flag characters are matched - a corresponding value.
 *         Otherwise - 0.
 */
unsigned char flag_handle(const char *flag, char *index)
{
	int i, j;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (ret == 0)
					ret = flags[j].value;
				else
					ret |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (ret);
}

/**
 * len_handle - Matches length modifiers with their corresponding value.
 * @opts: A pointer to a potential length modifier.
 * @index: An index counter for the original format string.
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Otherwise - 0.
 */
unsigned char len_handle(const char *opts, char *index)
{
	if (*opts == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*opts == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * width_handle - Matches a width modifier with its corresponding value.
 * @list: A va_list of arguments.
 * @opts: A pointer to a potential width modifier.
 * @index: An index counter for the original format string.
 * Return: If a width modifier is matched - its value.
 *         Otherwise - 0.
 */
int width_handle(va_list list, const char *opts, char *index)
{
	int ret = 0;

	while ((*opts >= '0' && *opts <= '9') || (*opts == '*'))
	{
		(*index)++;

		if (*opts == '*')
		{
			ret = va_arg(list, int);
			if (ret <= 0)
				return (0);
			return (ret);
		}

		ret *= 10;
		ret += (*opts - '0');
		opts++;
	}

	return (ret);
}

/**
 * prec_handle - Matches a precision modifier with
 * @list: A va_list of arguments.
 * @opts: A pointer to a potential precision modifier.
 * @index: An index counter for the original format string.
 * Return: If a precision modifier is matched - its value.
 *         If the precision modifier is empty, zero, or negative - 0.
 *         Otherwise - -1.
 */
int prec_handle(va_list list, const char *opts, char *index)
{
	int ret = 0;

	if (*opts != '.')
		return (-1);

	opts++;
	(*index)++;

	if ((*opts <= '0' || *opts > '9') &&
	     *opts != '*')
	{
		if (*opts == '0')
			(*index)++;
		return (0);
	}

	while ((*opts >= '0' && *opts <= '9') ||
	       (*opts == '*'))
	{
		(*index)++;

		if (*opts == '*')
		{
			ret = va_arg(list, int);
			if (ret <= 0)
				return (0);
			return (ret);
		}

		ret *= 10;
		ret += (*opts - '0');
		opts++;
	}

	return (ret);
}

/**
 * type_handle -  Matches a print option type with
 *                a corresponding print function.
 * @opts: A pointer to a potential print option type.
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*type_handle(const char *opts))(va_list, buffer_t *,
unsigned char, int, int, unsigned char)
{
	int i;
	print_t _tprint[] = {
		{'c', print_c},
		{'s', print_s},
		{'d', print_di},
		{'i', print_di},
		{'%', print_percent},
		{'b', print_b},
		{'u', print_u},
		{'o', print_o},
		{'x', print_hex},
		{'X', print_HEX},
		{'S', print_ns},
		{'p', print_add},
		{'r', print_r},
		{'R', print_R},
		{0, NULL}
	};

	for (i = 0; _tprint[i].fun; i++)
	{
		if (_tprint[i].type == *opts)
			return (_tprint[i].fun);
	}

	return (NULL);
}
