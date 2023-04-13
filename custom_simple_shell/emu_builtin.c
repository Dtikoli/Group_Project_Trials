#include "main.h"

/**
 * _myhistory - displays the history list, one command per line, preceded
 *              with line numbers, starting from  0.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * _myalias - mimics the alias builtin
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_print_alias(node);
			node = node->next;
		}
		return (0);
	}

	while (info->argv[j])
	{
		ptr = _strchr(info->argv[j], '=');
		if (ptr)
			_set_alias(info, info->argv[j]);
		else
			_print_alias(node_starts_with(info->alias, info->argv[j], '='));
		j++;
	}

	return (0);
}

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] is not equal "exit"
 */
int _myexit(info_t *info)
{
	int check_exit;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		check_exit = _err_atoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			_print_err(info, "Illegal number: ");
			_err_puts(info->argv[1]);
			_err_putc('\n');
			return (1);
		}
		info->err_num = _err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *ptr, *dir, buff[1024];
	int ret_chdir;

	ptr = getcwd(buff, 1024);
	if (!ptr)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			ret_chdir = /*  */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			ret_chdir = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(ptr);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ret_chdir = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		ret_chdir = chdir(info->argv[1]);
	if (ret_chdir == -1)
	{
		_print_err(info, "can't cd to ");
		_err_puts(info->argv[1]), _err_putc('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arv;

	arv = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arv);
	return (0);
}

