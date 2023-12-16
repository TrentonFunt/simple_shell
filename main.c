#include "shell.h"

/**
 * main - entry point
 * @ac: cmdArgs count
 * @av: cmdArgs vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	dataX info[] = { DATA_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				putsIN(av[0]);
				putsIN(": 0: Can't open ");
				putsIN(av[1]);
				putcharIN('\n');
				putcharIN(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->getFileDes = fd;
	}
	fillEnvList(info);
	hRead(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
