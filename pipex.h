/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:09:58 by cluco             #+#    #+#             */
/*   Updated: 2022/01/18 18:19:20 by cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		tmp_fd;
	char	**cmd1;
	char	**cmd2;
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
}				t_pipex;

void	replace_cmd(t_pipex *p, int n, char *str);
void	close_and_free(char *s, t_pipex *p, char *message, int cmd);
void	launch_which(char *cmd, char **env, t_pipex *p);
int		get_next_line(char **line, int fd);
void	cmd1(t_pipex *p, char **env, char **argv);
void	cmd2(t_pipex *p, char **env, char **argv);

#endif