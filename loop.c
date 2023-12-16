#include "shell.h"

/**
 * hsh - main shell loop
 * @shellData: the parameter & return shellData struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(dataX *shellData, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clrData(shellData);
		if (iMode(shellData))
			_puts("$ ");
		putcharIN(FLUSH_BUFFER);
		r = takeInput(shellData);
		if (r != -1)
		{
			defData(shellData, av);
			builtin_ret = builtIn(shellData);
			if (builtin_ret == -1)
				cmd_g(shellData);
		}
		else if (iMode(shellData))
			_putchar('\n');
		freeData(shellData, 0);
	}
	historyWrite(shellData);
	freeData(shellData, 1);
	if (!iMode(shellData) && shellData->shellState)
		exit(shellData->shellState);
	if (builtin_ret == -2)
	{
		if (shellData->errValue == -1)
			exit(shellData->shellState);
		exit(shellData->errValue);
	}
	return (builtin_ret);
}

/**
 * builtIn - finds a builtin command
 * @shellData: the parameter & return shellData struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int builtIn(dataX *shellData)
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
		if (_strcmp(shellData->cmdArgv[0], builtintbl[i].type) == 0)
		{
			shellData->cmdCounter++;
			built_in_ret = builtintbl[i].func(shellData);
			break;
		}
	return (built_in_ret);
}

/**
 * cmd_g - finds a command in PATH
 * @shellData: the parameter & return shellData struct
 *
 * Return: void
 */
void cmd_g(dataX *shellData)
{
	char *filePath = NULL;
	int i, k;

	shellData->filePath = shellData->cmdArgv[0];
	if (shellData->cmdCounterFlag == 1)
	{
		shellData->cmdCounter++;
		shellData->cmdCounterFlag = 0;
	}
	for (i = 0, k = 0; shellData->cmdArgs[i]; i++)
		if (!checkDelim(shellData->cmdArgs[i], " \t\n"))
			k++;
	if (!k)
		return;

	filePath = varPath(shellData, defEnv(shellData, "PATH="), shellData->cmdArgv[0]);
	if (filePath)
	{
		shellData->filePath = filePath;
		cmd_f(shellData);
	}
	else
	{
		if ((iMode(shellData) || defEnv(shellData, "PATH=")
			|| shellData->cmdArgv[0][0] == '/') && cmdRun(shellData, shellData->cmdArgv[0]))
			cmd_f(shellData);
		else if (*(shellData->cmdArgs) != '\n')
		{
			shellData->shellState = 127;
			printError(shellData, "not found\n");
		}
	}
}

/**
 * cmd_f - forks a an exec thread to run cmd
 * @shellData: the parameter & return shellData struct
 *
 * Return: void
 */
void cmd_f(dataX *shellData)
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
		if (execve(shellData->filePath, shellData->cmdArgv, envGet(shellData)) == -1)
		{
			freeData(shellData, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(shellData->shellState));
		if (WIFEXITED(shellData->shellState))
		{
			shellData->shellState = WEXITSTATUS(shellData->shellState);
			if (shellData->shellState == 126)
				printError(shellData, "Permission denied\n");
		}
	}
}
