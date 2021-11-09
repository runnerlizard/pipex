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
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr_fd ("(null)", 1));
	while (s[i])
		write (fd, &s[i++], 1);
	return (i);
}

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

int	main(int argc, char *argv[])
{
	char	**newargv;
	int		i;
	int		file;

	if (argc != 5)
		return (ft_putstr_fd("Wrong arguments\n", 1));
	newargv = malloc(sizeof(char *) * argc);
	file = open("z.sh", O_TRUNC | O_WRONLY | O_CREAT, 0777);
	handle_pipex(argv, file);
	i = 0;
	while (argv[++i])
		newargv[i - 1] = argv[i];
	newargv[i - 1] = NULL;
	i = 0;
	if (execve("z.sh", newargv, NULL) == -1)
		perror("Cant execute\n");
	ft_putstr_fd("Error\n", 1);
	free(newargv);
	return (argc);
}
