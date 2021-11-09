/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:26:03 by cluco             #+#    #+#             */
/*   Updated: 2021/11/09 20:36:30 by cluco            ###   ########.fr       */
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

static int	ft_strcmp(const char *s1, const char *s2)
{
	int		diff;
	size_t	i;

	i = 0;
	while ((s1[i]) || (s2[i]))
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff > 0)
			return (1);
		else if (diff < 0)
			return (-1);
		else if ((s1[i] == 0) & (s2[i] == 0))
			return (0);
		i++;
	}
	return (0);
}

static void	handle_and(int argc, char *argv[], int file)
{
	if (argc != 6)
		exit (ft_putstr_fd("Wrong arguments. Must be 5.\n", 1));
	ft_putstr_fd(argv[3], file);
	ft_putstr_fd(" << ", file);
	ft_putstr_fd(argv[2], file);
	ft_putstr_fd(" | ", file);
	ft_putstr_fd(argv[4], file);
	ft_putstr_fd(" >> ", file);
	ft_putstr_fd(argv[5], file);
}

static int	handle_multiple(int argc, char *argv[], int file)
{
	int	i;

	ft_putstr_fd("< ", file);
	ft_putstr_fd(argv[1], file);
	ft_putstr_fd(" ", file);
	i = 2;
	while (i < argc - 2)
	{
		ft_putstr_fd(argv[i++], file);
		ft_putstr_fd(" | ", file);
	}
	ft_putstr_fd(argv[i++], file);
	ft_putstr_fd(" > ", file);
	ft_putstr_fd(argv[i], file);
	return (0);
}

int	main(int argc, char *argv[])
{
	char	**newargv;
	int		i;
	int		file;

	if (argc < 5)
		return (ft_putstr_fd("Wrong arguments. Must be 4 or more.\n", 1));
	newargv = malloc(sizeof(char *) * argc);
	file = open("z.sh", O_TRUNC | O_WRONLY | O_CREAT, 0777);
	ft_putstr_fd("#!/bin/bash\n", file);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		handle_and(argc, argv, file);
	else
		handle_multiple(argc, argv, file);
	ft_putstr_fd("\nrm z.sh", file);
	i = 0;
	while (argv[++i])
		newargv[i - 1] = argv[i];
	newargv[i - 1] = NULL;
	if (execve("z.sh", newargv, NULL) == -1)
		perror("Cant execute\n");
	return (ft_putstr_fd("Error\n", 1));
}
