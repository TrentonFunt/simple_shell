#include "shell.h"

/**
 * envGet - returns the string array copy of our environ
 * @shellData: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **envGet(dataX *shellData)
{
	if (!shellData->environ || shellData->diffEnv)
	{
		shellData->environ = lengthS(shellData->env);
		shellData->diffEnv = 0;
	}

	return (shellData->environ);
}

/**
 * envUnset - Remove an environment variable
 * @shellData: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int envUnset(dataX *shellData, char *var)
{
	list_t *node = shellData->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = beginT(node->str, var);
		if (p && *p == '=')
		{
			shellData->diffEnv = delNode(&(shellData->env), i);
			i = 0;
			node = shellData->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (shellData->diffEnv);
}

/**
 * envSet - Initialize a new environment variable,
 *             or modify an existing one
 * @shellData: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int envSet(dataX *shellData, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = shellData->env;
	while (node)
	{
		p = beginT(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			shellData->diffEnv = 1;
			return (0);
		}
		node = node->next;
	}
	newNode(&(shellData->env), buf, 0);
	free(buf);
	shellData->diffEnv = 1;
	return (0);
}
