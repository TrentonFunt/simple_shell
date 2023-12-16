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

	/* Set the file name in the dataX struct */
	info->fileName = av[0];

	/* Check if command arguments are provided */
	if (info->cmdArgs)
	{
		/* Split command arguments into an array of strings */
		info->cmdArgv = strtow(info->cmdArgs, " \t");

		/* Check if the command arguments array is not created */
		if (!info->cmdArgv)
		{
			/* Allocate memory for a default array with one element */
			info->cmdArgv = malloc(sizeof(char *) * 2);

			/* Check if memory allocation is successful */
			if (info->cmdArgv)
			{
				/* Duplicate the command argument and set the array */
				info->cmdArgv[0] = _strdup(info->cmdArgs);
				info->cmdArgv[1] = NULL;
			}
		}

		/* Count the number of elements in the command arguments array */
		for (i = 0; info->cmdArgv && info->cmdArgv[i]; i++)
			;

		/* Set the number of command arguments in the dataX struct */
		info->cmdArgc = i;

		/* Apply alias changes */
		aliasChange(info);

		/* Apply variable changes */
		variableChange(info);
	}
}

/**
 * freeData - Frees dataX struct fields
 * @info: Pointer to the dataX struct
 * @all: True if freeing all fields
 */
void freeData(dataX *info, int all)
{
	/* Free the cmdArgv field and set it to NULL */
	ffree(info->cmdArgv);
	info->cmdArgv = NULL;
	info->filePath = NULL;

	/* Check if freeing all fields is requested */
	if (all)
	{
		/* Check if cmdBuffer is not set before freeing cmdArgs */
		if (!info->cmdBuffer)
			free(info->cmdArgs);

		/* Check and free env field if it exists */
		if (info->env)
			noList(&(info->env));

		/* Check and free shellHistory field if it exists */
		if (info->shellHistory)
			noList(&(info->shellHistory));

		/* Check and free alias field if it exists */
		if (info->alias)
			noList(&(info->alias));

		/* Free the environ field and set it to NULL */
		ffree(info->environ);
		info->environ = NULL;

		/* Free cmdBuffer using getFree function */
		getFree((void **)info->cmdBuffer);

		/* Check and close getFileDes if it's greater than 2 */
		if (info->getFileDes > 2)
			close(info->getFileDes);

		/* Flush the buffer using _putchar */
		_putchar(FLUSH_BUFFER);
	}
}
