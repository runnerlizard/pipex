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

static void	close_and_free(char *s, t_pipex *p, char *message)
{
	int	i;
	int	j;
	int	k;

	if (message)
		perror(message);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '1')
			free(p);
		else if (s[i] == '3')
		{
			j = 0;
			while (p->cmd[j + 1])
				j++;
			while (j >= 0)
			{
				k = 0;
				while (p->cmd[j][k + 1])
					k++;
				while (k >= 0)
					free(p->cmd[j][k--]);
				free(p->cmd[j--]);
			}
		}
		/*else if (s[i] == '4')
			free(p->cmd);*/
		else if (s[i] == '5')
			close(p->file1);
		else if (s[i] == '6')
			close(p->file2);
	}
	exit(1);
}

static void fork_2(t_pipex *p, char **env, char **argv)
{
	p->pid1 = fork();
	if (p->pid1 == 0)
	{
		if (close(p->file2))
			perror("close");
		p->file1 = open(argv[1], O_RDONLY);
		if (p->file1 < 0)
			close_and_free("6341", p, argv[1]);
		if (close(p->fd[0]))
			perror("close");
		if ((dup2(p->file1, STDIN_FILENO) < 0) || (dup2(p->fd[1], STDOUT_FILENO) < 0))
			perror("dup2");
		execve(ft_strjoin("/usr/bin/", p->cmd[0][0]), p->cmd[0], env);
		close_and_free("3415", p, argv[2]);
	}
	else if (p->pid1 > 0)
	{
		if (wait(NULL) < 0)
			perror("wait");
		if (close(p->file1))
			perror("close");
		if (close(p->fd[1]))
			perror("close");
		if ((dup2(p->fd[0], STDIN_FILENO) < 0) || (dup2(p->file2, STDOUT_FILENO) < 0))
			perror("dup2");
		execve(ft_strjoin("/usr/bin/", p->cmd[1][0]), p->cmd[1], env);
		close_and_free("6341", p, argv[3]);
	}
	else
		close_and_free("3416", p, "fork");
}

static void check_init_args(t_pipex *p, int argc, char **argv)
{
	int		i;

	if (argc != 5)
	{
		ft_printf("Must be 4 arguments!");
		close_and_free("1", p, NULL);
	}
	p->file2 = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0664);
	if (p->file2 < 0)
		close_and_free("1", p, argv[4]);
	if (!(p->cmd = malloc(sizeof(**(p->cmd)) * (argc - 2))))
		close_and_free("16", p, "malloc p->cmd");
	i = -1;
	while (++i < argc - 3)
		if (!(p->cmd[i] = ft_split(argv[2 + i], ' ')))
			close_and_free("641", p, "malloc p->cmd[i]");
}

int	main(int argc, char *argv[], char **env)
{
	t_pipex	*p;
	
	if (!(p = malloc(sizeof(p))))
		return (ft_putstr_fd("Malloc error.\n", 1));
	check_init_args(p, argc, argv);
	if (!pipe(p->fd))
		fork_2(p, env, argv);
	close_and_free("6341", p, "pipe");
}
