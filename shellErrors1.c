#include "shell.h"

/**
 *putsIN - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void putsIN(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putcharIN(str[i]);
		i++;
	}
}

/**
 * putcharIN - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putcharIN(char c)
{
	static int i;
	static char buf[OUTPUT_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= OUTPUT_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 * _putFileDes - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putFileDes(char c, int fd)
{
	static int i;
	static char buf[OUTPUT_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= OUTPUT_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 *_putsFileDes - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsFileDes(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putFileDes(*str++, fd);
	}
	return (i);
}
