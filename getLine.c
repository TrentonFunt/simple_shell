#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @shellData: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(dataX *shellData, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*getFree((void **)shellData->cmdBuffer);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, intHandle);
#if INIT_SYSTEM_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getLine(shellData, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			shellData->cmdCounterFlag = 1;
			remove_comments(*buf);
			hBuild(shellData, *buf, shellData->historyVal++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				shellData->cmdBuffer = buf;
			}
		}
	}
	return (r);
}

/**
 * takeInput - gets a line minus the newline
 * @shellData: parameter struct
 *
 * Return: bytes read
 */
ssize_t takeInput(dataX *shellData)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(shellData->cmdArgs), *p;

	_putchar(FLUSH_BUFFER);
	r = input_buf(shellData, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		chainChecks(shellData, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (chainDelim(shellData, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			shellData->cmdBufferType = NORMAL_COMMAND;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getLine() */
	return (r); /* return length of buffer from _getLine() */
}

/**
 * read_buf - reads a buffer
 * @shellData: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(dataX *shellData, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(shellData->getFileDes, buf, INPUT_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getLine - gets the next line of input from STDIN
 * @shellData: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getLine(dataX *shellData, char **ptr, size_t *length)
{
	static char buf[INPUT_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(shellData, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
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
