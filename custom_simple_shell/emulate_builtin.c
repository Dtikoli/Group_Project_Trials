#include "main.h"

/**
 * _hshhistory - displays history list.
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int _hshhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * _hshalias - mimics alias builtin
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int _hshalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_alias_print(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			_alias_set(info, info->argv[i]);
		else
			_alias_print(node_strstart(info->alias, info->argv[i], '='));
	}

	return (0);
}


/**
 * _hshexit - shell exit builtin
 * @info: Struct containing potential arguments.
 *  Return: exits with the specified exit status
 */
int _hshexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = err_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			err_print(info, "Illegal number: ");
			err_puts(info->argv[1]);
			err_putc('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _hshcd - controls changes of directories
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int _hshcd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		err_print(info, "can't cd to ");
		err_puts(info->argv[1]), err_putc('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", get_env(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _hshhelp - controls help calls
 * @info: Struct containing potential arguments.
 * Return: Always 0
 */
int _hshhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
