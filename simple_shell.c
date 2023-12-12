#include "simple_shell.h"

/**
 * main - This is the entry point for our shell program.
 * Return: Always 0.
 */
int main(void)
{
	char *usrInput; /* For storing user input from the command line */
	char *cmd_str; /* For storing the extracted command from user input */

	do {
		displayPrompt(); /* Display the shell prompt to the user */
		usrInput = readUserInput(); /* Reads user input from command line */
		cmd_str = extractCommand(usrInput); /*Extract command from userinput*/

		if (cmd_str != NULL)
		{
			executeCommand(cmd_str); /* Executes the extracted command */
			free(cmd_str); /* Frees the allocated memory for the command */
		}

		free(usrInput); /* Frees the allocated memory for the user input */

	} while (1);

	return (0);
}
