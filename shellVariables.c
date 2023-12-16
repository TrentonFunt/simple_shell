#include "shell.h"

/**
 * chainDelim - test if current char in buffer is a chain delimeter
 * @shellData: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chainDelim(dataX *shellData, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		shellData->cmdBufferType = OR_COMMAND;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		shellData->cmdBufferType = AND_COMMAND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		shellData->cmdBufferType = CHAINED_COMMAND;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chainChecks - checks we should continue chaining based on last shellState
 * @shellData: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void chainChecks(dataX *shellData, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (shellData->cmdBufferType == AND_COMMAND)
	{
		if (shellData->shellState)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (shellData->cmdBufferType == OR_COMMAND)
	{
		if (!shellData->shellState)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * aliasChange - replaces an aliases in the tokenized string
 * @shellData: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int aliasChange(dataX *shellData)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = beginNode(shellData->alias, shellData->cmdArgv[0], '=');
		if (!node)
			return (0);
		free(shellData->cmdArgv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		shellData->cmdArgv[0] = p;
	}
	return (1);
}

/**
 * variableChange - replaces vars in the tokenized string
 * @shellData: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int variableChange(dataX *shellData)
{
	int i = 0;
	list_t *node;

	for (i = 0; shellData->cmdArgv[i]; i++)
	{
		if (shellData->cmdArgv[i][0] != '$' || !shellData->cmdArgv[i][1])
			continue;

		if (!_strcmp(shellData->cmdArgv[i], "$?"))
		{
			stringChange(&(shellData->cmdArgv[i]),
				_strdup(convert_number(shellData->shellState, 10, 0)));
			continue;
		}
		if (!_strcmp(shellData->cmdArgv[i], "$$"))
		{
			stringChange(&(shellData->cmdArgv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = beginNode(shellData->env, &shellData->cmdArgv[i][1], '=');
		if (node)
		{
			stringChange(&(shellData->cmdArgv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		stringChange(&shellData->cmdArgv[i], _strdup(""));

	}
	return (0);
}

/**
 * stringChange - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int stringChange(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
