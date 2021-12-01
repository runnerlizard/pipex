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

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

/*
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
	ft_putstr_fd("\nrm z.sh", file);
}

static int check_args(int argc, char **argv, char **newargv)
{
	if (argc != 5)
		return (ft_putstr_fd("Error: must be 4 arguments.\n", 1));
	if (access(argv[1], 1) != 0)
	{
		perror(argv[1]);
		return (1);
	}
	if ((access(argv[4], 0) == 0) && (access(argv[4], 2) != 0))
	{
		perror(argv[1]);
		return (1);
	}
	if (!(newargv = malloc(sizeof(char *) * argc)))
		return (ft_putstr_fd("Error: malloc failed.\n", 1));
	return (0);	
}
*/
int	main(int argc, char *argv[])
{
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
	
	
	handle_pipex(argv, file);
	i = 0;
	while (argv[++i])
		newargv[i - 1] = argv[i];
	newargv[i - 1] = NULL;
	i = 0;
	if (execve("z.sh", newargv, NULL) == -1)
		perror("Cant execute\n");
	ft_putstr_fd("Error\n", 1);
	
	while (!(wait(0)) || (errno != ECHILD))
		;
	free(newargv);*/
	int	pid;
	char **args;
	args = malloc(sizeof(char *) * 5);
	args[0] = "ping";
	args[1]  = "google.cotm";
	args[2] = NULL;
 
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/ping", args, NULL);
		ft_putstr_fd("didnt happened\n", 1);
	}
	else
	{
		wait(NULL);
		ft_putstr_fd(argv[1], 1);
	}
	return (argc);
}
