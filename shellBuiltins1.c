#include "shell.h"

/**
 * exitDone - exits the shell
 * @shellData: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit shellState
 *         (0) if shellData.cmdArgv[0] != "exit"
 */
int exitDone(dataX *shellData)
{
	int exitcheck;

	if (shellData->cmdArgv[1])  /* If there is an exit arguement */
	{
		exitcheck = convertError(shellData->cmdArgv[1]);
		if (exitcheck == -1)
		{
			shellData->shellState = 2;
			printError(shellData, "Illegal number: ");
			putsIN(shellData->cmdArgv[1]);
			putcharIN('\n');
			return (1);
		}
		shellData->errValue = convertError(shellData->cmdArgv[1]);
		return (-2);
	}
	shellData->errValue = -1;
	return (-2);
}

/**
 * cdDone - changes the current directory of the process
 * @shellData: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int cdDone(dataX *shellData)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!shellData->cmdArgv[1])
	{
		dir = defEnv(shellData, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = defEnv(shellData, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(shellData->cmdArgv[1], "-") == 0)
	{
		if (!defEnv(shellData, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(defEnv(shellData, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = defEnv(shellData, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shellData->cmdArgv[1]);
	if (chdir_ret == -1)
	{
		printError(shellData, "can't cd to ");
		putsIN(shellData->cmdArgv[1]), putcharIN('\n');
	}
	else
	{
		envSet(shellData, "OLDPWD", defEnv(shellData, "PWD="));
		envSet(shellData, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * helpDone - changes the current directory of the process
 * @shellData: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int helpDone(dataX *shellData)
{
	char **arg_array;

	arg_array = shellData->cmdArgv;
	_puts("Not Implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
