#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;
	char	c;

	i = 0;
	c = '\n';
	while (s[i])
		write (fd, &s[i++], 1);
	write (fd, &c, 1);
}
