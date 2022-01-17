#include "pipex.h"

int get_next_line(char **line, int fd)
{
	int		rd;
	int		i;
	char	ch;
	char	*buffer;

	rd = 0;
	i = 0;
	buffer = ft_calloc(10, 10);
	*line = buffer;
	while ((rd = read(fd, &ch, 1)) > 0 && ch != '\n')
		buffer[i++] = ch;
	buffer[i] = '\0';
	if (ft_strlen(buffer) == 0)
		free(buffer);
	return (rd);
}

static void realloc_cmd(t_pipex *p, char **new, int n)
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

	//ft_printf("path %s, cmd2 %s\n", path, cmd[0]);
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
		{
			//ft_printf("%d  %s\n", ft_strlen(cmd[i]), cmd[i]);
			new[i] = ft_strjoin("", cmd[i]);
			//ft_printf("new[i] %s i  %d\n", new[i], i);
		}
		new[i] = NULL;
	}
	else
		return (NULL);
	return (new);
}

void	launch_which(char *cmd, char **env, t_pipex *p)
{
    char    *args[3];

    args[0] = "which";
	args[1] = cmd;
    args[2] = NULL;
    if (dup2(p->tmp_fd, 1) < 0)
        close_and_free("1234560", p, "clucotmpfile", 0);
    execve("/usr/bin/which", args, env);
	free(args[1]);
	close_and_free("30", p, "whichchild", 0);
}

void	replace_cmd(t_pipex *p, int n, char *str)
{
	if (n == 1)
		realloc_cmd(p, get_new(str, p->cmd1), 1);
	else if (n == 2)
		realloc_cmd(p, get_new(str, p->cmd2), 2);
}
