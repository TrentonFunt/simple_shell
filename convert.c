#include "shell.h"

/**
 * iMode - returns true if shell is iMode mode
 * @shellData: struct address
 *
 * Return: 1 if iMode mode, 0 otherwise
 */
int iMode(dataX *shellData)
{
	return (isatty(STDIN_FILENO) && shellData->getFileDes <= 2);
}

/**
 * checkDelim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int checkDelim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 *checkAlpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */
int checkAlpha(int c)
{
	if ((q >= 'a' && q <= 'z') || (q >= 'A' && q <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convert - converts a string to an integer
 * @s: the string to be converted
 * 
 * Return: 0 if no numbers in string, converted number otherwise
 */
int convert(char *s)
{
	int i = 0, sign = 1, output = 0;

	while (s[i] != '\0' && (s[i] == ' ' || (s[i] >= '0' && s[i] <= '9')))
	{
		/* Check for negative sign */
		if (s[i] == '-')
			sign *= -1;
		/* Convert character to digit and update output */
		else if (s[i] >= '0' && s[i] <= '9')
			output = output * 10 + (s[i] - '0');
		i++;
	}

	return (sign * output);
}
