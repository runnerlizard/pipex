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

static int check_init_args(t_pipex *p, int argc, char **argv)
{
	int		i;

	if (argc != 5)
		return (1);
	p->file1 = open(argv[1], O_RDONLY);
	if (p->file1 < 0)
		return(ft_printf("%s: %s\n", argv[1], strerror(errno)));
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

int	main(int argc, char *argv[])
{
	t_pipex	*p;
	
	if (!(p = malloc(sizeof(p))))
		return (ft_putstr_fd("Malloc error.\n", 1));
	if (check_init_args(p, argc, argv))
		return (0);
	p->pid = fork();
	if (p->pid == 0)
	{
		execve(ft_strjoin("/usr/bin/", p->cmd[0][0]), p->cmd[0], NULL);
		ft_putstr_fd("didnt happened\n", 1);
	}
	else
	{
		wait(NULL);
		ft_putstr_fd("\nDone\n", 1);
	}
	return (0);


	/*	char	**newargv;
	int		id;
	int		fd[2];
	char	*x;
	char	*y;

	newargv = NULL;
	if (check_args(argc, argv, newargv) != 0)
		return (1);
	//fd[0] = open(argv[1], O_RDONLY);
	if (!pipe(fd))
	{	
		id = fork();
		if (id == -1)
		{
			perror ("fork");
			return (1);
		}
		if (id == 0)
		{
			if (close(fd[0]))
				perror("close\n");
			x = "From child";
			if (write(fd[1], &x, sizeof(x)) == -1)
			{
				perror("write\n");
				return (1);
			}
			if (close(fd[1]))
				perror("close\n");
		}
		else
		{
			if (close(fd[1]))
				perror("close\n");
			if (read(fd[0], &y, sizeof(y)) == -1)
			{
				perror("read\n");
				return (1);
			}
			if (close(fd[0]))
				perror("close\n");
			printf("Got %s\n", y);
		}
	}
	else
	{
		perror ("pipe");
		return (1);
	}
	
	while (!(wait(0)) || (errno != ECHILD))
		;
	free(newargv);*/
}
