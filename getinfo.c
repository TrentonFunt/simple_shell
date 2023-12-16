#include "shell.h"

/**
 * clrData - initializes dataX struct
 * @shellData: struct address
 */
void clrData(dataX *shellData)
{
	shellData->cmdArgs = NULL;
	shellData->cmdArgv = NULL;
	shellData->filePath = NULL;
	shellData->cmdArgc = 0;
}

/**
 * defData - initializes dataX struct
 * @shellData: struct address
 * @av: argument vector
 */
void defData(dataX *shellData, char **av)
{
	int i = 0;

	shellData->fileName = av[0];
	if (shellData->cmdArgs)
	{
		shellData->cmdArgv = strtow(shellData->cmdArgs, " \t");
		if (!shellData->cmdArgv)
		{

			shellData->cmdArgv = malloc(sizeof(char *) * 2);
			if (shellData->cmdArgv)
			{
				shellData->cmdArgv[0] = _strdup(shellData->cmdArgs);
				shellData->cmdArgv[1] = NULL;
			}
		}
		for (i = 0; shellData->cmdArgv && shellData->cmdArgv[i]; i++)
			;
		shellData->cmdArgc = i;

		aliasChange(shellData);
		variableChange(shellData);
	}
}

/**
 * freeData - frees dataX struct fields
 * @shellData: struct address
 * @all: true if freeing all fields
 */
void freeData(dataX *shellData, int all)
{
	ffree(shellData->cmdArgv);
	shellData->cmdArgv = NULL;
	shellData->filePath = NULL;
	if (all)
	{
		if (!shellData->cmdBuffer)
			free(shellData->cmdArgs);
		if (shellData->env)
			noList(&(shellData->env));
		if (shellData->shellHistory)
			noList(&(shellData->shellHistory));
		if (shellData->alias)
			noList(&(shellData->alias));
		ffree(shellData->environ);
			shellData->environ = NULL;
		getFree((void **)shellData->cmdBuffer);
		if (shellData->getFileDes > 2)
			close(shellData->getFileDes);
		_putchar(FLUSH_BUFFER);
	}
}
