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
	pid_t	pid1;
}				t_pipex;

char    *get_path(char *str, t_pipex *p, char **env);
void	close_and_free(char *s, t_pipex *p, char *message, int cmd);
void    launch_cmd(t_pipex *p, char **argv, char **env);

#endif