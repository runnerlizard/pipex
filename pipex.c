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

static void free_eto(char s, t_pipex *p)
{
	int	j;
	int	k;

	if (s == '1')
		free(p);
	else if (s == '3')
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
	else if (s == '4')
		free(p->cmd);
}

static void	close_and_free(char *s, t_pipex *p, char *message, int cmd)
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
		if ((s[i] == '1') || (s[i] == '3') || (s[i] == '4'))
			free_eto(s[i], p);
		else if (s[i] == '2')
			unlink("clucotestfile");
		else if (s[i] == '5')
			close(p->file1);
		else if (s[i] == '6')
			close(p->file2);
	}
	exit(1);
}

int get_next_line(char **line, int fd)
{
	int rd;
	int i;
	char ch;
	char *buffer;

	rd = 0;
	i = 0;
	buffer = malloc(100);
	*line = buffer;
	while ((rd = read(fd, &ch, 1)) > 0 && ch != '\n')
		buffer[i++] = ch;
	buffer[i] = '\0';
	return (rd);
}

static char	*get_path(char *str, t_pipex *p, char **env)
{
	int		tmp_fd;
	pid_t	pid;
	char	*args[3];
	char	*path;

	tmp_fd = open("clucotestfile", O_TRUNC | O_CREAT | O_RDWR, 0664);
	pid = fork();
	if (pid == 0)
	{
		args[0] = "which";
		args[1] = str;
		args[2] = NULL;
		if (dup2(tmp_fd, STDOUT_FILENO) < 0)
			perror("dup2");
		execve("/usr/bin/which", args, env);
	}
	else if (pid > 0)
	{
		tmp_fd = open("clucotestfile", O_RDONLY);
		if (wait(NULL) < 0)
			perror("wait");
		get_next_line(&path, tmp_fd);
		free(str);
		return (path);
	}
	close_and_free("3412", p, "get_path", 0);
	return (NULL);
}

static void cmd1(t_pipex *p, char **env, char **argv)
{
	p->file1 = open(argv[1], O_RDONLY);
	if (p->file1 < 0)
		close_and_free("341", p, argv[1], 0);
	if (close(p->fd[0]))
		perror("close");
	if ((dup2(p->file1, STDIN_FILENO) < 0) || (dup2(p->fd[1], STDOUT_FILENO) < 0))
		perror("dup2");
	p->file2 = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0664);
	execve(p->cmd[0][0], p->cmd[0], env);
	close_and_free("3415", p, argv[2], 1);
}

static void cmd2(t_pipex *p, char **env, char **argv)
{
	if (wait(NULL) < 0)
		perror("wait");
	p->file2 = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0664);
	if (p->file2 < 0)
		close_and_free("341", p, argv[4], 0);
	if (close(p->fd[1]))
		perror("close");
	if ((dup2(p->fd[0], STDIN_FILENO) < 0) || (dup2(p->file2, STDOUT_FILENO) < 0))
		perror("dup2");
	execve(p->cmd[1][0], p->cmd[1], env);
	close_and_free("6341", p, argv[3], 1);
}
	
int	main(int argc, char *argv[], char **env)
{
	t_pipex	*p;
	int		i;
	
	if (argc != 5)
		return (ft_printf("Must be 4 arguments!"));
	if (!(p = malloc(sizeof(*p))))
		return (ft_putstr_fd("Malloc error.\n", 1));
	if (!(p->cmd = ft_calloc(sizeof(*(p->cmd)), 3)))
		close_and_free("1", p, "malloc p->cmd", 0);
	i = -1;
	while (++i < argc - 3)
		if (!(p->cmd[i] = ft_split(argv[2 + i], ' ')))
			close_and_free("41", p, "malloc p->cmd[i]", 0);
	p->cmd[0][0] = get_path(p->cmd[0][0], p, env);
	p->cmd[1][0] = get_path(p->cmd[1][0], p, env);
	if (pipe(p->fd))
		close_and_free("3412", p, "pipe", 0);
	p->pid1 = fork();
	unlink("clucotestfile");
	if (p->pid1 == 0)
		cmd1(p, env, argv);
	else if (p->pid1 > 0)
		cmd2(p, env, argv);
	close_and_free("341", p, "fork", 0);
}
