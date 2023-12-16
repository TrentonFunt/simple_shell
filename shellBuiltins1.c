#include "shell.h"

/**
 * exitDone - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit shellState
 *         (0) if info.cmdArgv[0] != "exit"
 */
int exitDone(dataX *info)
{
	int exitcheck;

	if (info->cmdArgv[1])  /* If there is an exit arguement */
	{
		exitcheck = convertError(info->cmdArgv[1]);
		if (exitcheck == -1)
		{
			info->shellState = 2;
			printError(info, "Illegal number: ");
			putsIN(info->cmdArgv[1]);
			putcharIN('\n');
			return (1);
		}
		info->errValue = convertError(info->cmdArgv[1]);
		return (-2);
	}
	info->errValue = -1;
	return (-2);
}

/**
 * cdDone - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int cdDone(dataX *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->cmdArgv[1])
	{
		dir = defEnv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = defEnv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->cmdArgv[1], "-") == 0)
	{
		if (!defEnv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(defEnv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = defEnv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->cmdArgv[1]);
	if (chdir_ret == -1)
	{
		printError(info, "can't cd to ");
		putsIN(info->cmdArgv[1]), putcharIN('\n');
	}
	else
	{
		envSet(info, "OLDPWD", defEnv(info, "PWD="));
		envSet(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * helpDone - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int helpDone(dataX *info)
{
	char **arg_array;

	arg_array = info->cmdArgv;
	_puts("Not Implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
