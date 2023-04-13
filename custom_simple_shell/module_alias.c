#include "main.h"

/**
 * _unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int _unset_alias(info_t *info, char *str)
{
	char *ptr, ch;
	int _ret;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	_ret = delete_node_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = ch;
	return (_ret);
}

/**
 * _set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int _set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (_unset_alias(info, str));

	_unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int _print_alias(list_t *node)
{
	char *ptr = NULL, *p = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (p = node->str; p <= ptr; p++)
			_putchar(*p);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

