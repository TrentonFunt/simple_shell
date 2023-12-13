#include "simple_shell.h"

/**
 * extractCommand - Extracts the command from the input line
 * @inputLine: The input line
 * Return: The extracted command
 */
char *extractCommand(char *inputLine)
{
	char *str_token;
	size_t len, i;
	char *cmd_str = NULL;

  /* Tokenizes the input line using space, tab, and newline as delimiters */
	str_token = strtok(inputLine, " \t\n");
	/* Checks if the token exists and if there is no additional token */
	if (str_token != NULL && strtok(NULL, " \t\n") == NULL)
	{
		len = 0;
		while (str_token[len] != '\0')
		{
			len++;
		}

		cmd_str = (char *)malloc(len + 1);
		if (cmd_str == NULL)
		{
			perror("Error allocating memory");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i <= len; i++)
		{
			cmd_str[i] = str_token[i];
		}
	}
	/* Displays an error message if multiple tokens exist */
	else if (str_token != NULL)
	{
		printf("Error: wrong command format\n");
	}

	return (cmd_str);
}
