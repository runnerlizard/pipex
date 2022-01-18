/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:32:33 by cluco             #+#    #+#             */
/*   Updated: 2022/01/18 18:32:33 by cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (c > 256)
		c = c - 256;
	while (str[i])
	{
		if (str[i] == c)
			j = i;
		i++;
	}
	if (c == 0)
		return ((char *)&str[i]);
	if ((str[0] != c) & (j == 0) & (c != 0))
		return (NULL);
	return ((char *)&str[j]);
}
