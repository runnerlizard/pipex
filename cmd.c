#include "pipex.h"

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

void    launch_cmd(t_pipex *p, char **argv, char **env)
{
    p->pid1 = fork();
	if (p->pid1 == 0)
		cmd1(p, env, argv);
	else if (p->pid1 > 0)
		cmd2(p, env, argv);
	close_and_free("341", p, "fork", 0);
}
