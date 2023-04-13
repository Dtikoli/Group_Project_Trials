#include "main.h"

/**
 * _is_cmd - identifies command arguments
 * @info: info struct
 * @path: path to file
 * Return: 1 if successful, 0 otherwise
 */
int _is_cmd(info_t *info, char *path)
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
 *_dup_chars - duplicates chars
 * @pathstr: PATH list string
 * @start: start index
 * @stop: stop index
 * Return: pointer to new buffer
 */
char *_dup_chars(char *pathstr, int start, int stop)
{
	static char buff[BUFF_SIZE];
	int i, j;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buff[j++] = pathstr[i];
	buff[j] = 0;
	return (buff);
}

/**
 * _find_path - finds current cmd in the PATH string
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 * Return: path of cmd if successful, or NULL if otherwise
 */
char *_find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, cur = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && _starts_with(cmd, "./"))
	{
		if (_is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = _dup_chars(pathstr, cur, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (_is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			cur = i;
		}
		i++;
	}
	return (NULL);
}

