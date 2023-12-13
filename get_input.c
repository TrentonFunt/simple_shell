#include "simple_shell.h"

/**
 * readUserInput - Reads a line of input from the user
 * Return: The user input as a string
 */
char *readUserInput(void)
{
	/**
	* This is to initialize userInput to NULL before reading user input
	* to prevent random addresses.
	*/
	char *usrInput = NULL;
	/* Initializes len to 0 for dynamic allocation of buffer size by getline. */
	size_t len = 0;

	/* Reads a line from the stdin into userInput */
	if (getline(&usrInput, &len, stdin) == -1)
	{
		/* Checks if end of file i.e (Ctrl+D) was reached */
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		/* Prints an error and exits with failure if getline fails */
		perror("Error reading user input");
		exit(EXIT_FAILURE);
	}

	return (usrInput);
}
