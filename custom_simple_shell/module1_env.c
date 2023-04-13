#include "main.h"

/**
 * _push_env_list - populates env linked list
 * @info: Structure containing potential argumements
 * Return: Always 0
 */
int _push_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * _get_environ - returns the string array copy of shell's environ
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **_get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes an environment variable
 * @info: Structure containing potential arguments.
 * Return: 1 successful, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = _starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environ var or modify an existing one
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		ptr = _starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
