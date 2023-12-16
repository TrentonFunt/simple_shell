#include "shell.h"

/**
 * historyDone - displays the shellHistory list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @shellData: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int historyDone(dataX *shellData)
{
	listPrint(shellData->shellHistory);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @shellData: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(dataX *shellData, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delNode(&(shellData->alias),
		nodeIndex(shellData->alias, beginNode(shellData->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @shellData: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(dataX *shellData, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(shellData, str));

	unset_alias(shellData, str);
	return (newNode(&(shellData->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * aliasDone - mimics the alias builtin (man alias)
 * @shellData: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int aliasDone(dataX *shellData)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (shellData->cmdArgc == 1)
	{
		node = shellData->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shellData->cmdArgv[i]; i++)
	{
		p = _strchr(shellData->cmdArgv[i], '=');
		if (p)
			set_alias(shellData, shellData->cmdArgv[i]);
		else
			print_alias(beginNode(shellData->alias, shellData->cmdArgv[i], '='));
	}

	return (0);
}
