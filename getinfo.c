#include "shell.h"

/**
 * clrData - initializes dataX struct
 * @info: struct address
 */
void clrData(dataX *info)
{
	info->cmdArgs = NULL;
	info->cmdArgv = NULL;
	info->filePath = NULL;
	info->cmdArgc = 0;
}

/**
 * defData - initializes dataX struct
 * @info: struct address
 * @av: argument vector
 */
void defData(dataX *info, char **av)
{
	int i = 0;

	info->fileName = av[0];
	if (info->cmdArgs)
	{
		info->cmdArgv = strtow(info->cmdArgs, " \t");
		if (!info->cmdArgv)
		{

			info->cmdArgv = malloc(sizeof(char *) * 2);
			if (info->cmdArgv)
			{
				info->cmdArgv[0] = _strdup(info->cmdArgs);
				info->cmdArgv[1] = NULL;
			}
		}
		for (i = 0; info->cmdArgv && info->cmdArgv[i]; i++)
			;
		info->cmdArgc = i;

		aliasChange(info);
		variableChange(info);
	}
}

/**
 * freeData - frees dataX struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeData(dataX *info, int all)
{
	ffree(info->cmdArgv);
	info->cmdArgv = NULL;
	info->filePath = NULL;
	if (all)
	{
		if (!info->cmdBuffer)
			free(info->cmdArgs);
		if (info->env)
			noList(&(info->env));
		if (info->shellHistory)
			noList(&(info->shellHistory));
		if (info->alias)
			noList(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		getFree((void **)info->cmdBuffer);
		if (info->getFileDes > 2)
			close(info->getFileDes);
		_putchar(FLUSH_BUFFER);
	}
}
