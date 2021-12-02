#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		file1;
	int		file2;
	char	***cmd;
	int		fd[2];
	int		pid;
}				t_pipex;

#endif