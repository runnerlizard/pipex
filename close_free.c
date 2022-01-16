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
		while (p->cmd[j])
			j++;
		free (p->cmd[j--]);
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
