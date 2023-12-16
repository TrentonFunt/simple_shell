#include "shell.h"

/**
 * cmdRun - determines if a file is an executable command
 * @info: the info struct
 * @filePath: filePath to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int cmdRun(dataX *info, char *filePath)
{
	struct stat st;

	(void)info;
	if (!filePath || stat(filePath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * genChar - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *genChar(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * varPath - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full filePath of cmd if found or NULL
 */
char *varPath(dataX *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *filePath;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && beginT(cmd, "./"))
	{
		if (cmdRun(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			filePath = genChar(pathstr, curr_pos, i);
			if (!*filePath)
				_strcat(filePath, cmd);
			else
			{
				_strcat(filePath, "/");
				_strcat(filePath, cmd);
			}
			if (cmdRun(info, filePath))
				return (filePath);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
