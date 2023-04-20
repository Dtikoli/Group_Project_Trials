#include "main.h"

/**
 * _buff_input - buffer's chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t _buff_input(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, _sigint_handle);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n') /* remove trailing '\n' */
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			handle_comments(*buf);
			hist_build(info, *buf, info->histcount++);
			 /* Check for command chains */
			if (_strchr(*buf, ';') || _strstr(*buf, "&&") || _strstr(*buf, "||"))
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * _getinput - gets a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t _getinput(info_t *info)
{
	static char *buf; /* ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFF_FLUSH);
	r = _buff_input(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* there are commands left in the chain buffer */
	{
		j = i; /* initialise iterator to current buffer position */
		p = buf + i; /* get pointer for return */

		_chain_check(info, buf, &j, i, len);
		while (j < len)
		{
			if (_ischain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0; /* reset buffer length and position */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * _buff_read - reads the buffer
 * @info: struct containing potential arguments
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t _buff_read(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - retrieves the next line of input from STDIN
 * @info: struct containing potential arguments
 * @ptr: double pointer to buffer
 * @length: size of malloc'd buffer if not NULL
 * Return: length of next line
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = _buff_read(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * _sigint_handle - blocks CTRL-C
 * @sig_num: signal inumber
 * Return: Nothing
 */
void _sigint_handle(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
