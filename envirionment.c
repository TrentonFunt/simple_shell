#include "shell.h"

/**
 * envDone - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int envDone(dataX *info)
{
	strPrint(info->env);
	return (0);
}

/**
 * defEnv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *defEnv(dataX *info, const char *name)
{
	list_t *node = info->env;
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
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int setEnvDone(dataX *info)
{
	if (info->cmdArgc != 3)
	{
		putsIN("Incorrect number of arguements\n");
		return (1);
	}
	if (envSet(info, info->cmdArgv[1], info->cmdArgv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvDone - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unsetEnvDone(dataX *info)
{
	int i;

	if (info->cmdArgc == 1)
	{
		putsIN("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->cmdArgc; i++)
		envUnset(info, info->cmdArgv[i]);

	return (0);
}

/**
 * fillEnvList - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fillEnvList(dataX *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		newNode(&node, environ[i], 0);
	info->env = node;
	return (0);
}
