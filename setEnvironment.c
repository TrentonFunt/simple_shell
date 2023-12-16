#include "shell.h"

/**
 * envGet - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **envGet(dataX *info)
{
	if (!info->environ || info->diffEnv)
	{
		info->environ = lengthS(info->env);
		info->diffEnv = 0;
	}

	return (info->environ);
}

/**
 * envUnset - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int envUnset(dataX *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = beginT(node->str, var);
		if (p && *p == '=')
		{
			info->diffEnv = delNode(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->diffEnv);
}

/**
 * envSet - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int envSet(dataX *info, char *var, char *value)
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
	node = info->env;
	while (node)
	{
		p = beginT(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->diffEnv = 1;
			return (0);
		}
		node = node->next;
	}
	newNode(&(info->env), buf, 0);
	free(buf);
	info->diffEnv = 1;
	return (0);
}
