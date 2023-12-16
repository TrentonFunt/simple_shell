#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(dataX *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /*  fill buffer if empty */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, intHandle);
#if INIT_SYSTEM_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getLine(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /*  trailing newline removed */
				r--;
			}
			info->cmdCounterFlag = 1;
			remove_comments(*buf);
			hBuild(info, *buf, info->historyVal++);
			{
				*len = r;
				info->cmdBuffer = buf;
			}
		}
	}
	return (r);
}

/**
 * takeInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t takeInput(dataX *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->cmdArgs), *p;

	_putchar(FLUSH_BUFFER);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* End Of File Condition */
		return (-1);
	if (len)
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		chainChecks(info, buf, &j, i, len);
		while (j < len)
		{
			if (chainDelim(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmdBufferType = NORMAL_COMMAND;
		}

		*buf_p = p;
		return (_strlen(p)); /* length of command */
	}

	*buf_p = buf; /* if not a chain, pass from _getLine() */
	return (r); /* rlength of buffer */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(dataX *info, char *buf, size_t *i)
{
	ssize_t q = 0;

	if (*i)
		return (0);
	q = read(info->getFileDes, buf, INPUT_BUFFER_SIZE);
	if (q >= 0)
		*i = q;
	return (q);
}

/**
 * _getLine - gets the next line of input from STDIN
 * @info: parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: The number of characters read, or -1 on failure.
 */
int _getLine(dataX *info, char **ptr, size_t *length)
{
	/* Static buffer for reading input */
	static char buf[INPUT_BUFFER_SIZE];
	static size_t i = 0, len = 0;
	ssize_t r = 0, s = 0;
	ssize_t k;
	char *p = *ptr, *new_p = NULL, *c;

	/* Check if a preallocated buffer and its size are provided */
	if (p && length)
		s = *length;

	/* Reset indices if the current buffer is fully consumed */
	if (i == len) {
		i = len = 0;
		/* Read from input into the buffer */
		r = read_buf(info, buf, &len);
		if (r == -1 || (r == 0 && len == 0))
			return (-1);
	}

	/* Find the position of the newline character in the buffer */
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	/* Allocate memory for the new buffer based on the length */
	new_p = _realloc(p, s, s ? s + k : k + 1);

	/* Check for memory allocation failure */
	if (!new_p)
		return (p ? free(p), -1 : -1);

	/* Copy the contents of the buffer to the new buffer */
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	/* Update indices and pointers */
	s += k - i;
	i = k;
	p = new_p;

	/* Update the provided length if applicable */
	if (length)
		*length = s;

	/* Update the pointer to the buffer */
	*ptr = p;
	return (s);
}

/**
 * intHandle - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void intHandle(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}
