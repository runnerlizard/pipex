#ifndef PIPEX_H
#define PIPEX_H

#include "./libft/libft.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img_p;
	void	*img_w;
	void	*img_g;
	void	*img_c;
	void	*img_e;
	int		lines;
	int		columns;
	int		map_height;
	int		map_width;
	char	*map;
	int		end_num;
	int		movescount;
	int		img_width;
	int		img_height;
	int		numb;
}				t_vars;



#endif
