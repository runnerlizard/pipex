#include "pipex.h"

static void    launch_which(char *str, int tmp_fd, char **env)
{
    char    *args[3];

    args[0] = "which";
    args[1] = str;
    args[2] = NULL;
    if (dup2(tmp_fd, STDOUT_FILENO) < 0)
        perror("dup2");
    execve("/usr/bin/which", args, env);
}

static int get_next_line(char **line, int fd)
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

char    *get_path(char *str, t_pipex *p, char **env)
{
	int		tmp_fd;
	pid_t	pid;
	char	*path;

	tmp_fd = open("clucotestfile", O_TRUNC | O_CREAT | O_RDWR, 0664);
	pid = fork();
	if (pid == 0)
        launch_which(str, tmp_fd, env);
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
