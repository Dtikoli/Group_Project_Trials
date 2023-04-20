#include "main.h"

/**
 * _alias_unset - unsets the alias
 * @info: struct containing potential arguments
 * @str: string alias
 * Return: 0 on success, 1 otherwise
 */
int _alias_unset(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_index(&(info->alias),
		get_node_index(info->alias, node_strstart(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _alias_set - sets alias to string
 * @info: struct containing potential arguments
 * @str: string alias
 * Return: 0 on success, 1 otherwise
 */
int _alias_set(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_alias_unset(info, str));

	_alias_unset(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _alias_print - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int _alias_print(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
