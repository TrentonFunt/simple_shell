#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (!str || str[0] == '\0')
		return (NULL);

	if (!d)
		d = " ";

	/* Count the number of words */
	for (i = 0; str[i] != '\0'; i++)
		if (!checkDelim(str[i], d) && (checkDelim(str[i + 1], d) || str[i + 1] == '\0'))
			numwords++;

	if (numwords == 0)
		return (NULL);

	s = malloc((numwords + 1) * sizeof(char *));
	if (!s)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		/* Skip delimiters */
		while (checkDelim(str[i], d))
			i++;

		/* Count characters until the next delimiter or end of string */
		k = 0;
		while (!checkDelim(str[i + k], d) && str[i + k] != '\0')
			k++;

		/* Allocate memory for the word */
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		/* Copy characters into the new word */
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];

		/* Null-terminate the word */
		s[j][m] = '\0';
	}

	/* Null-terminate the array of strings */
	s[j] = NULL;
	return (s);
}

/**
 * **strtowTwo - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtowTwo(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
