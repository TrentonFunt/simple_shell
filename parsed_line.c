#include "simple_shell.h"

/**
 * extractCommand - Extracts the command from the input line
 * @inputLine: The input line
 * Return: The extracted command
 */
char *extractCommand(char *inputLine)
{
	char *str_token;
	char *cmd_str = NULL;

  /* Tokenizes the input line using space, tab, and newline as delimiters */
	str_token = strtok(inputLine, " \t\n");
	/* Checks if the token exists and if there is no additional token */
	if (str_token != NULL && strtok(NULL, " \t\n") == NULL)
	{
		/**
		 * Allocates the memory for the command string
		 * @strdup: then copies the token
		 */
		cmd_str = strdup(str_token);
		/* Checks for memory allocation failure */
		if (cmd_str == NULL)
		{
			perror("Error allocating memory");
			exit(EXIT_FAILURE);
		}
	}
	/* Displays an error message if multiple tokens exist */
	else if (str_token != NULL)
	{
		printf("Error: The command must be a single word\n");
	}

	return (cmd_str);
}
