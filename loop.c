#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(dataX *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clrData(info);
		if (iMode(info))
			_puts("$ ");
		putcharIN(FLUSH_BUFFER);
		r = takeInput(info);
		if (r != -1)
		{
			defData(info, av);
			builtin_ret = builtIn(info);
			if (builtin_ret == -1)
				cmd_g(info);
		}
		else if (iMode(info))
			_putchar('\n');
		freeData(info, 0);
	}
	historyWrite(info);
	freeData(info, 1);
	if (!iMode(info) && info->shellState)
		exit(info->shellState);
	if (builtin_ret == -2)
	{
		if (info->errValue == -1)
			exit(info->shellState);
		exit(info->errValue);
	}
	return (builtin_ret);
}

/**
 * builtIn - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int builtIn(dataX *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exitDone},
		{"env", envDone},
		{"help", helpDone},
		{"shellHistory", historyDone},
		{"setenv", setEnvDone},
		{"unsetenv", unsetEnvDone},
		{"cd", cdDone},
		{"alias", aliasDone},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->cmdArgv[0], builtintbl[i].type) == 0)
		{
			info->cmdCounter++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * cmd_g - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void cmd_g(dataX *info)
{
	char *filePath = NULL;
	int i, k;

	info->filePath = info->cmdArgv[0];
	if (info->cmdCounterFlag == 1)
	{
		info->cmdCounter++;
		info->cmdCounterFlag = 0;
	}
	for (i = 0, k = 0; info->cmdArgs[i]; i++)
		if (!checkDelim(info->cmdArgs[i], " \t\n"))
			k++;
	if (!k)
		return;

	filePath = varPath(info, defEnv(info, "PATH="), info->cmdArgv[0]);
	if (filePath)
	{
		info->filePath = filePath;
		cmd_f(info);
	}
	else
	{
		if ((iMode(info) || defEnv(info, "PATH=")
			|| info->cmdArgv[0][0] == '/') && cmdRun(info, info->cmdArgv[0]))
			cmd_f(info);
		else if (*(info->cmdArgs) != '\n')
		{
			info->shellState = 127;
			printError(info, "not found\n");
		}
	}
}

/**
 * cmd_f - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void cmd_f(dataX *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->filePath, info->cmdArgv, envGet(info)) == -1)
		{
			freeData(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->shellState));
		if (WIFEXITED(info->shellState))
		{
			info->shellState = WEXITSTATUS(info->shellState);
			if (info->shellState == 126)
				printError(info, "Permission denied\n");
		}
	}
}
