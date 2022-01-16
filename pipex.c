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

static t_pipex *malloc_p(int argc, char **argv)
{
	t_pipex	*p;
	int		i;

	if (!(p = malloc(sizeof(*p))))
		close_and_free("", p, "malloc p->cmd", 0);
	if (!(p->cmd = ft_calloc(sizeof(*(p->cmd)), 3)))
		close_and_free("1", p, "malloc p->cmd", 0);
	i = -1;
	while (++i < argc - 3)
		if (!(p->cmd[i] = ft_split(argv[2 + i], ' ')))
			close_and_free("41", p, "malloc p->cmd[i]", 0);
	return (p);
}
	
int	main(int argc, char *argv[], char **env)
{
	t_pipex	*p;
	
	if (argc != 5)
		return (ft_printf("Must be 4 arguments!"));
	p = malloc_p(argc, argv);
	p->cmd[0][0] = get_path(p->cmd[0][0], p, env);
	p->cmd[1][0] = get_path(p->cmd[1][0], p, env);
	if (pipe(p->fd))
		close_and_free("3412", p, "pipe", 0);
	unlink("clucotestfile");
	launch_cmd(p, argv, env);
}
