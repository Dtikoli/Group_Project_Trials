#include "main.h"

/**
 * _hsh - main shell loop function
 * @info: the parameter & return info struct
 * @arv: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int _hsh(info_t *info, char **arv)
{
	ssize_t j = 0;
	int ret_builtin = 0;

	while (j != -1 && ret_builtin != -2)
	{
		_clear_info(info);
		if (_interact(info))
			_puts("$ ");
		_err_putc(BUF_FLUSH);
		ret_builtin = _get_input(info);
		if (j != -1)
		{
			_set_info(info, arv);
			ret_builtin = _find_builtin(info);
			if (ret_builtin == -1)
				_find_cmd(info);
		}
		else if (_interact(info))
			_putchar('\n');
		_free_info(info, 0);
	}
	_write_hist(info);
	_free_info(info, 1);
	if (!_interact(info) && info->status)
		exit(info->status);
	if (ret_builtin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (ret_builtin);
}

/**
 * _find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found, -2 if signals exit,
 *		0 if executed successfully, 1 if unsuccessful,
 */
int _find_builtin(info_t *info)
{
	int j, ret_builtin = -1;
	builtin_t builtintable[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (j = 0; builtintable[j].type; j++)
		if (_strcmp(info->argv[0], builtintable[j].type) == 0)
		{
			info->line_count++;
			ret_builtin = builtintable[j].func(info);
			break;
		}
	return (ret_builtin);
}

/**
 * _find_cmd - finds a command in the PATH list
 * @info: parameter & return info struct
 * Return: nothing
 */
void _find_cmd(info_t *info)
{
	char *path = NULL;
	int j, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (j = 0, k = 0; info->arg[j]; j++)
		if (!_is_delim(info->arg[j], " \t\n"))
			k++;
	if (!k)
		return;

	path = _find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_fork_cmd(info);
	}
	else
	{
		if ((_interact(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && _is_cmd(info, info->argv[0]))
			_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_print_err(info, "not found\n");
		}
	}
}

/**
 * _fork_cmd - forks a an executed thread to run cmd
 * @info: parameter & return info struct
 * Return: nothing
 */
void _fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, _get_environ(info)) == -1)
		{
			_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_print_err(info, "Permission denied\n");
		}
	}
}
