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

#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int		*n;
	char	***cmd;

	if (argc != 5)
		return (1);
	if (!(n = malloc(sizeof(int) * 2)))
		return (ft_putstr_fd("Malloc error.\n", 1));
	if (!(cmd = malloc(sizeof(**cmd) * (argc - 2))))
		return (ft_putstr_fd("Malloc error 1.\n", 1));
	n[0] = -1;
	while (++n[0] < argc - 3)
		if (!(cmd[n[0]] = ft_split(argv[2 + n[0]], ' ')))
			return (ft_putstr_fd("Malloc error 2.\n", 1));
	n[1]= fork();
	if (n[1] == 0)
	{
		execve(ft_strjoin("/usr/bin/", cmd[0][0]), cmd[0], NULL);
		ft_putstr_fd("didnt happened\n", 1);
	}
	else
	{
		wait(NULL);
		ft_putstr_fd("\nDone\n", 1);
	}
	return (argc);


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
