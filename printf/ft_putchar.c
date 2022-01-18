/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:29:25 by cluco             #+#    #+#             */
/*   Updated: 2022/01/18 18:29:25 by cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpercent(char c)
{
	char	percent;

	percent = '%';
	if ((c == 'i') || (c == 'd') || (c == 'c') || (c == 's') || (c == 'p')
		|| (c == 'u') || (c == 'x') || (c == 'X'))
		return (0);
	if (c == '%')
	{
		write (1, &c, 1);
		return (1);
	}
	else
	{
		write (1, &percent, 1);
		write (1, &c, 1);
		return (2);
	}
}

int	ft_putchar(int n)
{
	write(1, &n, 1);
	return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr_fd ("(null)", 1));
	while (s[i])
		write (fd, &s[i++], 1);
	return (i);
}

int	ft_count(int d)
{
	static int	count;
	int			tmp;

	tmp = 0;
	if (d == -1)
	{
		tmp = count;
		count = 0;
		return (tmp);
	}
	count = count + d;
	return (count);
}
