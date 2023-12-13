#include "simple_shell.h"

/**
 * exit_Shell - Checks if the given command is the "exit" command
 * @command: The command to check
 * Return: 1 if the command is "exit," 0 otherwise
 */
int exit_Shell(char *command)
{
	char *args[10];
	int isExit, i;

	args[0] = strtok(command, " ");
	/* Checks if the command is the built-in "exit" command using strcmp */
	if (args[0] != NULL)
	{
		isExit = 1;
		for (i = 0; i < 4; i++)
		{
			if (args[0][i] != "exit"[i])
			{
				isExit = 0;
				break;
			}
		}
		if (isExit)
		{
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

/**
 * create_CP - Forks and executes the given command in a child process
 * @args: Array of strings representing the command and its arguments
 */
void create_CP(char *args[])
{
	pid_t pid; /* Variable to store the Process ID of child */
	int status;

	/* Forks a new process to execute the command */
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error while executing command");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			/* Parent process that waits for child process to execute */
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		/**
		* Continue looping until the child process has either
		* exited normally (WIFEXITED) or has been terminated
		* by a signal (WIFSIGNALED).
		*/
	}
}

/**
 * executeCommand - Executes the given command
 * @command: The command to execute
 */
void executeCommand(char *command)
{
	int i;
	char *token; /* Pointer to the current token during command parsing */
	char *args[10];

	/* Uses strtok to break down the command string into individual tokens.*/
	token = strtok(command, " ");

	i = 0;
	while (token != NULL)
	{
		args[i++] = token; /* This stores the tokens in the args array */
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* Checks if the command is "exit" and exit if true */
	if (exit_Shell(command))
	{
		exit(EXIT_SUCCESS);
	}

	/* Creates a child process to execute the command */
	create_CP(args);
}
