#include "simple_shell.h"

/**
 * displayPrompt - Displays a shell prompt
 */
void displayPrompt(void)
{
	/**
	 * @isatty: Checks if the file descriptor refers to a terminal
	 */
	if (isatty(STDIN_FILENO))
	{
		printf("( ͡° ͜ʖ ͡°) "); /* Prints the shell prompt */
		fflush(stdout);	/* Flushes the stdout buffer */
	}
}
