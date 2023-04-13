#include "main.h"

/**
 * _is_chain - test if the current char in buffer is a chain delimeter
 * @info: parameter struct
 * @buff: char buffer
 * @ptr: buffer pointer
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _is_chain(info_t *info, char *buff, size_t *ptr)
{
	size_t i = *ptr;

	if (buff[i] == '|' && buff[i + 1] == '|')
	{
		buff[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[i] == '&' && buff[i + 1] == '&')
	{
		buff[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[i] == ';') /* found end of this command */
	{
		buff[i] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}

/**
 * _check_chain - ch chaining continuation based on last status
 * @info: parameter struct
 * @buff: char buffer
 * @ptr: pointer to buffer
 * @st: starting position in buffer
 * @len: length of buffer
 * Return: nothing
 */
void _check_chain(info_t *info, char *buff, size_t *ptr, size_t st, size_t len)
{
	size_t i = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[st] = 0;
			i = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[st] = 0;
			i = len;
		}
	}

	*ptr = i;
}

/**
 * _replace_alias - replace aliases in the tokenized string
 * @info: parameter struct
 * Return: 1 if successful, 0 otherwise
 */
int _replace_alias(info_t *info)
{
	int j = 0;
	char *ptr;
	list_t *node;

	while (j < 10)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
		j++;
	}
	return (1);
}

/**
 * _replace_vars - replaces vars in the tokenized string
 * @info: parameter struct
 * Return: 1 ifsuccesful, 0 otherwise
 */
int _replace_vars(info_t *info)
{
	int j = 0;
	list_t *node;

	while (info->argv[j])
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			_replace_string(&(info->argv[j]),
				_strdup(convert_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			_replace_string(&(info->argv[j]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[j][1], '=');
		if (node)
		{
			_replace_string(&(info->argv[j]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		_replace_string(&info->argv[j], _strdup(""));
		j++;
	}
	return (0);
}

/**
 * _replace_string - replaces  a previous string
 * @prev: address of previous string
 * @cur: new string
 * Return: 1 if successful, 0 otherwise
 */
int _replace_string(char **prev, char *cur)
{
	free(*prev);
	*prev = cur;
	return (1);
}

