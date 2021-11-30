#include "libft.h"

long int	ft_abs1(long int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

void	ft_write_small(int fd, long int n)
{
	char	res;

	res = n + 48;
	write(fd, &res, 1);
}

void	ft_write_big(int fd, long int n)
{
	char		res;
	long int	k;

	k = 10;
	while (n / k >= 10)
		k = k * 10;
	while (k >= 1)
	{
		res = (n % (10 * k)) / k + 48;
		write(fd, &res, 1);
		k = k / 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	n1;
	char		res;

	if (n < 0)
	{
		res = '-';
		write(fd, &res, 1);
	}
	n1 = ft_abs1(n);
	if (n1 > 9)
		ft_write_big(fd, n1);
	else
		ft_write_small(fd, n1);
}
