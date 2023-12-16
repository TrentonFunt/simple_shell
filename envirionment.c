#include "shell.h"

/**
 * envDone - prints the current environment
 * @shellData: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int envDone(dataX *shellData)
{
	strPrint(shellData->env);
	return (0);
}

/**
 * defEnv - gets the value of an environ variable
 * @shellData: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: value
 */
char *defEnv(dataX *shellData, const char *name)
{
	list_t *node = shellData->env;
	char *p;

	while (node)
	{
		p = beginT(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvDone - Initialize a new environment variable,
 *             or modify an existing one
 * @shellData: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int setEnvDone(dataX *shellData)
{
	if (shellData->cmdArgc != 3)
	{
		putsIN("Number of arguments incorrect\n");
		return (1);
	}
	if (envSet(shellData, shellData->cmdArgv[1], shellData->cmdArgv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvDone - Remove an environment variable
 * @shellData: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unsetEnvDone(dataX *shellData)
{
	int i;

	if (shellData->cmdArgc == 1)
	{
		putsIN("Arguments not enough.\n");
		return (1);
	}
	for (i = 1; i <= shellData->cmdArgc; i++)
		envUnset(shellData, shellData->cmdArgv[i]);

	return (0);
}

/**
 * fillEnvList - populates env linked list
 * @shellData: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fillEnvList(dataX *shellData)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		newNode(&node, environ[i], 0);
	shellData->env = node;
	return (0);
}
