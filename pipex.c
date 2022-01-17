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


static void free_eto(char s, t_pipex *p)
{
	int	j;

	if (s == '3')
		free(p);
	else if (s == '1')
	{
		j = 0;
		while (p->cmd1[j])
			j++;
		while (j >= 0)
			free(p->cmd1[j--]);
		free(p->cmd1);
	}
	else if (s == '2')
	{
		j = 0;
		while (p->cmd2[j])
			j++;
		while (j >= 0)
			free(p->cmd2[j--]);
		free(p->cmd2);
	}
}

void	close_and_free(char *s, t_pipex *p, char *message, int cmd)
{
	int	i;

	if ((message) && (cmd > 0))
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if ((message) && (cmd == 0))
		perror(message);
	i = -1;
	while (s[++i])
	{
		if ((s[i] == '1') || (s[i] == '2') || (s[i] == '3'))
			free_eto(s[i], p);
		else if (s[i] == '4')
			unlink("clucotmpfile");
		else if ((s[i] == '5') && (p->file1 > 0))
			close(p->file1);
		else if ((s[i] == '6') && (p->file2 > 0))
			close(p->file2);
		if (s[i] == '0')
			exit(1);
	}
}

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
	return (p);
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
		cmd1(p, env, argv);
	else if (p->pid1 > 0)
		cmd2(p, env, argv);
	else
		close_and_free("1230", p, "fork1", 0);
}
