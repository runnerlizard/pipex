#include "ft_printf.h"

int	ft_putnbr_fd (unsigned int n)
{
	unsigned int	i;
	unsigned int	d;
	char			c;
	int				count;

	i = 1;
	d = n;
	count = 0;
	if (n == 0)
		return (ft_putchar(48));
	while (d >= 10)
	{
		i = i * 10;
		d = d / 10;
	}
	while (i > 0)
	{
		d = n / i;
		c = d + 48;
		write (1, &c, 1);
		n = n % i;
		i = i / 10;
		count++;
	}
	return (count);
}

int	ft_print_sign (int n)
{
	unsigned int	d;
	char			c;
	int				count;

	d = n;
	count = 0;
	if (n < 0)
	{
		c = '-';
		write (1, &c, 1);
		d = -d;
		count++;
	}
	count = count + ft_putnbr_fd (d);
	return (count);
}

int	ft_hub_int(char c, int d)
{
	int	count;

	if ((c == 'd') || (c == 'i'))
		count = ft_print_sign (d);
	if (c == 'c')
		count = ft_putchar (d);
	return (count);
}

int	fl(char c, unsigned long d)
{
	int				count;

	if (c == 'u')
		count = ft_putnbr_fd (d);
	if (c == 'p')
		count = ft_print_p (d);
	if (c == 'x')
		count = ft_hex ((unsigned int)d, 1);
	if (c == 'X')
		count = ft_hex ((unsigned int)d, 2);
	return (count);
}
