/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:10:01 by cluco             #+#    #+#             */
/*   Updated: 2022/01/18 19:29:43 by cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_next_line(char **line, int fd)
{
	int		rd;
	int		i;
	char	ch;
	char	*buffer;

	rd = 0;
	i = 0;
	buffer = ft_calloc(10, 10);
	*line = buffer;
	rd = read(fd, &ch, 1);
	while ((rd) > 0 && ch != '\n')
	{
		buffer[i++] = ch;
		rd = read(fd, &ch, 1);
	}
	buffer[i] = '\0';
	if (ft_strlen(buffer) == 0)
		free(buffer);
	return (rd);
}

void	launch_which(char *cmd, char **env, t_pipex *p)
{
	char	*args[3];

	args[0] = "which";
	args[1] = cmd;
	args[2] = NULL;
	if (dup2(p->tmp_fd, 1) < 0)
		close_and_free("4561230", p, "clucotmpfile", 0);
	execve("/usr/bin/which", args, env);
	close_and_free("4561230", p, "whichchild", 0);
}

static void	realloc_cmd(t_pipex *p, char **new, int n)
{
	int		j;
	char	**tmp;

	if (n == 1)
	{
		tmp = p->cmd1;
		p->cmd1 = new;
	}
	else
	{
		tmp = p->cmd2;
		p->cmd2 = new;
	}
	j = 0;
	while (tmp[j])
		j++;
	while (j >= 0)
		free(tmp[j--]);
	free(tmp);
}

static char	**get_new(char *path, char **cmd)
{
	int		i;
	char	**new;

	if (path != NULL)
	{
		i = 1;
		while (cmd[i++])
			;
		i++;
		new = ft_calloc(sizeof(char *), i);
		new[0] = path;
		i = 0;
		while (cmd[++i])
			new[i] = ft_strjoin("", cmd[i]);
		new[i] = NULL;
	}
	else
		return (NULL);
	return (new);
}

void	replace_cmd(t_pipex *p, int n, char *str)
{
	if (n == 1)
		realloc_cmd(p, get_new(str, p->cmd1), 1);
	else if (n == 2)
		realloc_cmd(p, get_new(str, p->cmd2), 2);
}
