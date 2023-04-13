#include "main.h"

/**
 * _input_buff - buffer of chained commands
 * @info: parameter struct
 * @buff: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t _input_buff(info_t *info, char **buff, size_t *len)
{
	ssize_t r_count = 0;
	size_t len_p = 0;

	if (!*len) /* fill buffer if empty */
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, _sigint_handle);
#if USE_GETLINE
		r_count = getline(buff, &len_p, stdin);
#else
		r_count = _getline(info, buff, &len_p);
#endif
		if (r_count > 0)
		{
			if ((*buff)[r_count - 1] == '\n') /* remove trail. newlines */
			{
				(*buff)[r_count - 1] = '\0';
				r_count--;
			}
			info->linecount_flag = 1;
			_remove_comments(*buff);
			_build_hist_list(info, *buff, info->histcount++);
			{
				*len = r_count;
				info->cmd_buf = buff;
			}
		}
	}
	return (r_count);
}

/**
 * _get_input - gets a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t _get_input(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = _input_buff(info, &buff, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* there are  commands left in the chain buffer */
	{
		j = i; /* set new iterator to current buffer position */
		p = buff + i; /* get pointer for return */

		_check_chain(info, buff, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (_is_chain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len)
		{
			i = len = 0; /* reset length and position*/
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* return pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buff; /* else not a chain, pass back buffer  */
	return (r);
}

/**
 * _read_buff - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @size: buffer size
 * Return: length read
 */
ssize_t _read_buff(info_t *info, char *buff, size_t *size)
{
	ssize_t r_count = 0;

	if (*size)
		return (0);
	r_count = read(info->readfd, buff, BUFF_SIZE);
	if (r_count >= 0)
		*size = r_count;
	return (r_count);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = _read_buff(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

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
 * @sig_num: the signal number
 * Return: Nothing
 */
void _sigint_handle(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

