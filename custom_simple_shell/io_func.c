#include "main.h"

/**
 * _get_hist_file - retrieves the history file
 * @info: parameter struct
 * Return: malloc'd string containing history file
 */

char *_get_hist_file(info_t *info)
{
	char *buff, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (buff == NULL)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * _write_hist - creates or appent contents to a file
 * @info: the parameter struct
 * Return: 1 on success, otherwise -1
 */
int _write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = _get_hist_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_puts_fd(node->str, fd);
		_putc_fd('\n', fd);
	}
	_putc_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _read_hist - reads history from file
 * @info: the parameter struct
 * Return: history count on success, 0 otherwise
 */
int _read_hist(info_t *info)
{
	int i, last = 0, count = 0;
	ssize_t fd, r_len, size = 0;
	struct stat sta;
	char *buff = NULL, *filename = _get_hist_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &sta))
		size = sta.st_size;
	if (size < 2)
		return (0);
	buff = malloc(sizeof(char) * (size + 1));
	if (buff == NULL)
		return (0);
	r_len = read(fd, buff, size);
	buff[size] = 0;
	if (r_len <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < size; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			_build_hist_list(info, buff + last, count++);
			last = i + 1;
		}
	if (last != i)
		_build_hist_list(info, buff + last, count++);
	free(buff);
	info->histcount = count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_index(&(info->history), 0);
	_renum_hist(info);
	return (info->histcount);
}

/**
 * _build_hist_list - adds entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buff: buffer
 * @count: history linecount, histcount
 * Return: Always 0
 */
int _build_hist_list(info_t *info, char *buff, int count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * _renum_hist - renumbers history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 * Return: the new histcount
 */
int _renum_hist(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
