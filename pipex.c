/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:22:05 by cluco             #+#    #+#             */
/*   Updated: 2022/01/16 18:13:34 by cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipex *malloc_p(char **argv)
{
	t_pipex	*p;

	if (!(p = malloc(sizeof(*p))))
		perror("malloc1");
	if (!(p->cmd1 = ft_split(argv[2], ' ')))
		close_and_free("30", p, "malloc2", 0);
	if (!(p->cmd2 = ft_split(argv[3], ' ')))
		close_and_free("130", p, "malloc3", 0);
	p->file2 = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0664);
	p->file1 = open(argv[1], O_RDONLY);
	if (p->file1 < 0)
		perror(argv[1]);
	return (p);
}

static void cmd1(t_pipex *p, char **env, char **argv)
{
	char	*str;
	
	if (dup2(p->file1, STDIN_FILENO) < 0)
		close_and_free("12340", p, argv[1], 0);
	p->tmp_fd = open("clucotmpfile", O_TRUNC | O_CREAT | O_RDWR, 0664);
	if (p->tmp_fd < 0)
		close_and_free("1230", p, "clucotmpfile", 0);
	p->pid2 = fork();
	if (p->pid2 == 0)
        launch_which(p->cmd1[0], env, p);
	else if (p->pid2 > 0)
	{
		p->tmp_fd = open("clucotmpfile", O_RDONLY);
		if (wait(NULL) < 0)
			perror("wait1");
		get_next_line(&str, p->tmp_fd);
		replace_cmd(p, 1, str);
		if (close(p->fd[0]))
			perror("close");
		if (dup2(p->fd[1], STDOUT_FILENO) < 0)
			close_and_free("1234560", p, "dup[2]", 0);
		close_and_free("246", p, NULL, 0);
		execve(p->cmd1[0], p->cmd1, env);
		close_and_free("1350", p, p->cmd1[0], 1);
	}
	else
		close_and_free("1234560", p, "fork1", 0);
}

static void cmd2(t_pipex *p, char **env, char **argv)
{
	char	*str;
	
	if (wait(NULL) < 0)
		close_and_free("12340", p, argv[1], 0);
	p->file2 = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0664);
	if (p->file2 < 0)
		close_and_free("123450", p, argv[4], 0);
	p->tmp_fd = open("clucotmpfile", O_TRUNC | O_CREAT | O_RDWR, 0664);
	if (p->tmp_fd < 0)
		close_and_free("1230", p, "clucotmpfile", 0);
	p->pid2 = fork();
	if (p->pid2 == 0)
        launch_which(p->cmd2[0], env, p);
	else if (p->pid2 > 0)
	{
		p->tmp_fd = open("clucotmpfile", O_RDONLY);
		if (wait(NULL) < 0)
			perror("wait2");
		if (get_next_line(&str, p->tmp_fd) == 0)
			close_and_free("1234560", p, p->cmd2[0], 1);
		replace_cmd(p, 2, str);
		if (close(p->fd[1]))
			close_and_free("1234560", p, argv[1], 0);
		if ((dup2(p->fd[0], STDIN_FILENO) < 0) || (dup2(p->file2, STDOUT_FILENO) < 0))
			close_and_free("1234560", p, argv[1], 0);
		close_and_free("145", p, NULL, 0);
		execve(p->cmd2[0], p->cmd2, env);
		close_and_free("2360", p, p->cmd2[0], 1);
	}
	else
		close_and_free("1234560", p, "fork2", 0);
}

int	main(int argc, char *argv[], char **env)
{
	t_pipex	*p;
	
	if (argc != 5)
		return (ft_printf("Must be 4 arguments!"));
	p = malloc_p(argv);
	if (pipe(p->fd))
		close_and_free("1230", p, "pipe", 0);
	p->pid1 = fork();
	if (p->pid1 == 0)
	{
		if (p->file1 > 0)
			cmd1(p, env, argv);
	}
	else if (p->pid1 > 0)
		cmd2(p, env, argv);
	else
		close_and_free("1230", p, "fork1", 0);
}
