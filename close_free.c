#include "pipex.h"

static void free_eto(char s, t_pipex *p)
{
	int	j;

	if (s == '3')
		free(p);
	else if (s == '1')
	{
		j = 0;
		while (p->cmd1[j])
			j++;
		while (j >= 0)
			free(p->cmd1[j--]);
		free(p->cmd1);
	}
	else if (s == '2')
	{
		j = 0;
		while (p->cmd2[j])
			j++;
		while (j >= 0)
			free(p->cmd2[j--]);
		free(p->cmd2);
	}
}

void	close_and_free(char *s, t_pipex *p, char *message, int cmd)
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
		if ((s[i] == '1') || (s[i] == '2') || (s[i] == '3'))
			free_eto(s[i], p);
		else if (s[i] == '4')
			unlink("clucotmpfile");
		else if ((s[i] == '5') && (p->file1 > 0))
			close(p->file1);
		else if ((s[i] == '6') && (p->file2 > 0))
			close(p->file2);
		if (s[i] == '0')
			exit(1);
	}
}
