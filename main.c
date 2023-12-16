#include "shell.h"

/**
 * main - The entry point for the simple shell.
 * @argcCount: Count of command-line arguments - cmdArgsc
 * @argvArray: Array of command-line argument strings - cmdArgsv
 * Return: 0 on success, 1 on error
 */
int main(int argcCount, char **argvArray)
{
	dataX shellData[] = { DATA_INIT }; /* initializes shell data structure*/
	int fd = 2; /* FilDes for input */

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	/* Checks script file for command-line argument */
	if (argcCount == 2)
	{
		fd = open(argvArray[1], O_RDONLY); /* opens the script file for reading */
		if (fd == -1)
		{
			/* Handles file open errors based on errno */
			if (errno == EACCES)
				exit(126);
			/* Print error message for file not found */
			if (errno == ENOENT)
			{
				putsIN(argvArray[0]);
				putsIN(": 0: This can not open ");
				putsIN(argvArray[1]);
				putcharIN('\n');
				putcharIN(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shellData->getFileDes = fd; /* Update the filDes in shell data structure */
	}
	fillEnvList(shellData); /* Fill the environment list with initial values */
	hRead(shellData); /* Reads the command history from file */
	hsh(shellData, argvArray); /* Starts our main shell loop */
	return (EXIT_SUCCESS); /* Exits our simple shell with success status */
}
