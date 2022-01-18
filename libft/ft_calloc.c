/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:34:20 by cluco             #+#    #+#             */
/*   Updated: 2022/01/18 18:34:20 by cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	char		*res;
	size_t		i;

	i = 0;
	res = (char *)malloc(n * s);
	if (res == NULL)
		return (NULL);
	else
		while (i < (n * s))
			res[i++] = 0;
	return (res);
}
