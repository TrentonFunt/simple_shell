#include "shell.h"

/**
 * _strcmp - Performs lexicographic comparison of two strings.
 * @s1: The first string
 * @s2: The second string
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	/* Compare characters until a difference is found or both strings end */
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * beginT - Checks if needle starts with haystack.
 * @haystack: String to search
 * @needle: The substring to find
 *
 * Return: Address of the next character of haystack or NULL
 */
char *beginT(const char *haystack, const char *needle)
{
	/* Check if characters match until the end of the needle */
	while (*needle)
	{
		if (*needle != *haystack)
			return (NULL);

		needle++;
		haystack++;
	}

	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	/* Move to the end of the destination string */
	while (*dest)
		dest++;

	/* Copy characters from source to destination */
	while ((*dest++ = *src++))
		;

	return (ret);
}

/**
 * _strlen - Returns the length of a string.
 * @s: The string whose length to check
 *
 * Return: Integer length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);

	/* Count characters until the end of the string */
	while (*s++)
		len++;

	return (len);
}
