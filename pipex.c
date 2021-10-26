#include "pipex.h"

int main (int argc, char *argv[])
{
	char	*newargv[argc];
	int		i;
	int		file;

	if (argc != 5)
	return (1);
	file = open("my.sh", O_WRONLY, 0777);
	ft_putstr_fd("#!/bin/bash\n< ", file);
	ft_putstr_fd(argv[1], file);
	ft_putstr_fd(" ", file);
	ft_putstr_fd(argv[2], file);
	ft_putstr_fd(" | ", file);
	ft_putstr_fd(argv[3], file);
	ft_putstr_fd(" > ", file);
	ft_putstr_fd(argv[4], file);
	i = 0;
	while (argv[++i])
		newargv[i - 1] = argv[i];
	newargv[i - 1] = NULL;
	i = 0;
	if (execve("my.sh", newargv, NULL) == -1)
		perror("Cant execute\n");
	printf("Error\n");
	exit(argc);
}
