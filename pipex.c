/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:22:05 by cluco             #+#    #+#             */
/*   Updated: 2021/11/09 20:38:44 by cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int fork_2(t_pipex *p, char **env, char **argv)
{
	p->pid = fork();
	if (p->pid == 0)
	{
		p->file1 = open(argv[1], O_RDONLY);
		if (p->file1 < 0)
			return(ft_printf("%s: %s\n", argv[1], strerror(errno)));
		if (close(p->fd[0]))
			perror("close");
		if ((dup2(p->file1, STDIN_FILENO) < 0) || (dup2(p->fd[1], STDOUT_FILENO) < 0))
			perror("dup2");
		execve(ft_strjoin("/usr/bin/", p->cmd[0][0]), p->cmd[0], env);
		return (-1);
	}
	else if (p->pid > 0)
	{
		if (wait(NULL) < 0)
			perror("wait");
		if (close(p->fd[1]))
			perror("close");
		if ((dup2(p->fd[0], STDIN_FILENO) < 0) || (dup2(p->file2, STDOUT_FILENO) < 0))
			perror("dup2");
		execve(ft_strjoin("/usr/bin/", p->cmd[1][0]), p->cmd[1], env);
		return (-2);
	}
	else
		return (ft_printf("fork: %s\n", strerror(errno)));
	return (1);
}

static int check_init_args(t_pipex *p, int argc, char **argv)
{
	int		i;

	if (argc != 5)
		return (1);
	p->file2 = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0664);
	if (p->file2 < 0)
		return(ft_printf("%s: %s\n", argv[4], strerror(errno)));
	if (!(p->cmd = malloc(sizeof(**p->cmd) * (argc - 2))))
		return (ft_putstr_fd("Malloc error 1.\n", 1));
	i = -1;
	while (++i < argc - 3)
		if (!(p->cmd[i] = ft_split(argv[2 + i], ' ')))
			return (ft_putstr_fd("Malloc error 2.\n", 1));
	return (0);
}

int	main(int argc, char *argv[], char **env) //add closes and frees in error cases
{
	t_pipex	*p;
	
	if (!(p = malloc(sizeof(p))))
		return (ft_putstr_fd("Malloc error.\n", 1));
	if (check_init_args(p, argc, argv))
		return (0);
	if (!pipe(p->fd))
		return (fork_2(p, env, argv));
	else
		return(ft_printf("pipe: %s\n", strerror(errno)));
	return (0);
}
