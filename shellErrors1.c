#include "shell.h"

/**
 * putsIN - prints an input string
 * @str: the string to be printed
 *
 * Return: No return value
 */
void putsIN(char *str)
{
	int i = 0;

	/* Check if the input string is not NULL */
	if (str != NULL)
		return;

	/* Loop through the string and print each character */
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

	/* Check if c is FLUSH_BUFFER or buffer is full */
	if (c == FLUSH_BUFFER || i >= OUTPUT_BUFFER_SIZE)
	{
		write(2, buf, i); /* Write the buffer to stderr */
		i = 0;
	}
	/* Check if c is not FLUSH_BUFFER, then add it to the buffer */
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

	/* Check if c is FLUSH_BUFFER or buffer is full */
	if (c == FLUSH_BUFFER || i >= OUTPUT_BUFFER_SIZE)
	{
		write(fd, buf, i); /* Write the buffer to specified file descriptor */
		i = 0;
	}
	/* Check if c is not FLUSH_BUFFER, then add it to the buffer */
	if (c != FLUSH_BUFFER)
		buf[i++] = c;

	return (1);
}

/**
 * _putsFileDes - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsFileDes(char *str, int fd)
{
	int i = 0;

	/* Check if the input string is not NULL */
	if (str != NULL)

		return (0);

	/* Loop through the string and write each character to specified fd */
	while (*str)
	{
		i += _putFileDes(*str++, fd);
	}

	return (i);
}
