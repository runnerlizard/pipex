#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

static int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr_fd ("(null)", 1));
	while (s[i])
		write (fd, &s[i++], 1);
	return (i);
}

static void	handle_pipex(char *argv[], int file)
{
	ft_putstr_fd("#!/bin/bash\n< ", file);
	ft_putstr_fd(argv[1], file);
	ft_putstr_fd(" ", file);
	ft_putstr_fd(argv[2], file);
	ft_putstr_fd(" | ", file);
	ft_putstr_fd(argv[3], file);
	ft_putstr_fd(" > ", file);
	ft_putstr_fd(argv[4], file);
	ft_putstr_fd("\nrm my.sh", file);
}

int main (int argc, char *argv[])
{
	char	*newargv[argc];
	int		i;
	int		file;

	if (argc != 5)
		return (ft_putstr_fd("Wrong arguments\n", 1));
	file = open("my.sh", O_TRUNC | O_WRONLY | O_CREAT, 0777);
	handle_pipex(argv, file);
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
