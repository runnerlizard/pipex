#include "pipex.h"

static void	launch_cmd1(t_pipex *p, char **env)
{
	char	*str;
	
	p->tmp_fd = open("clucotmpfile", O_RDONLY);
	if (wait(NULL) < 0)
		perror("wait1");
	if (get_next_line(&str, p->tmp_fd) == 0)
		close_and_free("4561230", p, p->cmd1[0], 1);
	replace_cmd(p, 1, str);
	if (close(p->fd[0]))
		perror("close pipe");
	if (dup2(p->fd[1], STDOUT_FILENO) < 0)
		close_and_free("1234560", p, "dup2", 0);
	close_and_free("246", p, NULL, 0);
	execve(p->cmd1[0], p->cmd1, env);
	close_and_free("1350", p, p->cmd1[0], 1);
}

void cmd1(t_pipex *p, char **env, char **argv)
{
	if (p->file1 < 0)
		close_and_free("561230", p, argv[1], 0);
	if (dup2(p->file1, STDIN_FILENO) < 0)
		close_and_free("12340", p, "dup2", 0);
	p->tmp_fd = open("clucotmpfile", O_TRUNC | O_CREAT | O_RDWR, 0664);
	if (p->tmp_fd < 0)
		close_and_free("1230", p, "clucotmpfile", 0);
	p->pid2 = fork();
	if (p->pid2 == 0)
        launch_which(p->cmd1[0], env, p);
	else if (p->pid2 > 0)
		launch_cmd1(p, env);
	else
		close_and_free("1234560", p, "fork1", 0);
}

static void launch_cmd2(t_pipex *p, char **env)
{
	char	*str;
	
	p->tmp_fd = open("clucotmpfile", O_RDONLY);
	if (wait(NULL) < 0)
		perror("wait2");
	if (get_next_line(&str, p->tmp_fd) == 0)
		close_and_free("4561230", p, p->cmd2[0], 1);
	replace_cmd(p, 2, str);
	if (close(p->fd[1]))
		perror("close pipe");
	if ((dup2(p->fd[0], STDIN_FILENO) < 0) || (dup2(p->file2, STDOUT_FILENO) < 0))
		close_and_free("4561230", p, "dup2", 0);
	close_and_free("45", p, NULL, 0);
	execve(p->cmd2[0], p->cmd2, env);
	close_and_free("6230", p, p->cmd2[0], 1);
}

void	cmd2(t_pipex *p, char **env, char **argv)
{
	if (wait(NULL) < 0)
		close_and_free("561230", p, "wait", 0);
	p->file2 = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0664);
	if (p->file2 < 0)
		close_and_free("561230", p, argv[4], 0);
	p->tmp_fd = open("clucotmpfile", O_TRUNC | O_CREAT | O_RDWR, 0664);
	if (p->tmp_fd < 0)
		close_and_free("561230", p, "clucotmpfile", 0);
	p->pid2 = fork();
	if (p->pid2 == 0)
        launch_which(p->cmd2[0], env, p);
	else if (p->pid2 > 0)
		launch_cmd2(p, env);
	else
		close_and_free("1234560", p, "fork2", 0);
}
