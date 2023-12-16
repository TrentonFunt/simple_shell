#include "shell.h"

/**
 * getFileHistory - gets the shellHistory file
 * @info: parameter struct
 *
 * Return: allocated string containg shellHistory file
 */

char *getFileHistory(dataX *info)
{
	char *buf, *dir;

	dir = defEnv(info, "HOME=");
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
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int historyWrite(dataX *info)
{
	ssize_t fd;
	char *filename = getFileHistory(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->shellHistory; node; node = node->next)
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
 * @info: the parameter struct
 *
 * Return: historyVal on success, 0 otherwise
 */
int hRead(dataX *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getFileHistory(info);

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
			hBuild(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		hBuild(info, buf + last, linecount++);
	free(buf);
	info->historyVal = linecount;
	while (info->historyVal-- >= MAX_ENTRIES_HISTORY)
		delNode(&(info->shellHistory), 0);
	hNum(info);
	return (info->historyVal);
}

/**
 * hBuild - adds entry to a shellHistory linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the shellHistory linecount, historyVal
 *
 * Return: Always 0
 */
int hBuild(dataX *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->shellHistory)
		node = info->shellHistory;
	newNode(&node, buf, linecount);

	if (!info->shellHistory)
		info->shellHistory = node;
	return (0);
}

/**
 * hNum - renumbers the shellHistory linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new historyVal
 */
int hNum(dataX *info)
{
	list_t *node = info->shellHistory;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->historyVal = i);
}
