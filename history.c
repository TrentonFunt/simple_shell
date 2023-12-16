#include "shell.h"

/**
 * getFileHistory - gets the shellHistory file
 * @shellData: parameter struct
 *
 * Return: allocated string containg shellHistory file
 */

char *getFileHistory(dataX *shellData)
{
	char *buf, *dir;

	dir = defEnv(shellData, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(FILE_HISTORY) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, FILE_HISTORY);
	return (buf);
}

/**
 * historyWrite - creates a file, or appends to an existing file
 * @shellData: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int historyWrite(dataX *shellData)
{
	ssize_t fd;
	char *filename = getFileHistory(shellData);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = shellData->shellHistory; node; node = node->next)
	{
		_putsFileDes(node->str, fd);
		_putFileDes('\n', fd);
	}
	_putFileDes(FLUSH_BUFFER, fd);
	close(fd);
	return (1);
}

/**
 * hRead - reads shellHistory from file
 * @shellData: the parameter struct
 *
 * Return: historyVal on success, 0 otherwise
 */
int hRead(dataX *shellData)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getFileHistory(shellData);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			hBuild(shellData, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		hBuild(shellData, buf + last, linecount++);
	free(buf);
	shellData->historyVal = linecount;
	while (shellData->historyVal-- >= MAX_ENTRIES_HISTORY)
		delNode(&(shellData->shellHistory), 0);
	hNum(shellData);
	return (shellData->historyVal);
}

/**
 * hBuild - adds entry to a shellHistory linked list
 * @shellData: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the shellHistory linecount, historyVal
 *
 * Return: Always 0
 */
int hBuild(dataX *shellData, char *buf, int linecount)
{
	list_t *node = NULL;

	if (shellData->shellHistory)
		node = shellData->shellHistory;
	newNode(&node, buf, linecount);

	if (!shellData->shellHistory)
		shellData->shellHistory = node;
	return (0);
}

/**
 * hNum - renumbers the shellHistory linked list after changes
 * @shellData: Structure containing potential arguments. Used to maintain
 *
 * Return: the new historyVal
 */
int hNum(dataX *shellData)
{
	list_t *node = shellData->shellHistory;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (shellData->historyVal = i);
}
