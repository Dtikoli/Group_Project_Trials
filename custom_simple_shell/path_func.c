#include "main.h"

/**
 * _iscmd - checks if file is executable command
 * @info: struct containibg potential arguments
 * @path: file file
 * Return: 1 if true, 0 otherwise
 */
int _iscmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _chars_dup - duplicates chars
 * @pathstr: PATH list
 * @start: start index
 * @stop: stop index
 * Return: pointer to duplicated chars
 */
char *_chars_dup(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * _path_trace - searches for cmd in the PATH list
 * @info: struct containing potential arguments
 * @pathstr: PATH list
 * @cmd: command to find
 * Return: path of cmd if found, NULL otherwise
 */
char *_path_trace(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && _strstart(cmd, "./"))
	{
		if (_iscmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _chars_dup(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (_iscmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
