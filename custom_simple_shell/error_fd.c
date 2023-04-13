#include "main.h"

/**
 * _putc_fd - writes the chars to specified fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1, on error -1, and errno is set.
 */
int _putc_fd(char c, int fd)
{
	static int len;
	static char buff[BUFF_SIZE];

	if (c == BUF_FLUSH || len >= BUFF_SIZE)
	{
		write(fd, buff, len);
		len = 0;
	}
	if (c != BUF_FLUSH)
		buff[len++] = c;
	return (1);
}

/**
 *_puts_fd - prints an input string buffer
 * @str: string to be printed
 * @fd: filedescriptor to write to
 * Return: the number of chars written
 */
int _puts_fd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putc_fd(*str++, fd);
	}
	return (j);
}

