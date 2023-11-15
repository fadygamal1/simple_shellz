#include "shell.h"
/**
 * main - entry poin
 * @argc: count
 * @av: vector
 * Return: 0
 */
int main(int argc, char **av)
{
	inf_t in[] = { INF_INIT };
	int fd = 2;

	asm("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));
	if (argc == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		in->rfd = fd;
	}
	populate_env_list(in);
	r_hist(in);
	shell(in, av);
	return (EXIT_SUCCESS);
}

