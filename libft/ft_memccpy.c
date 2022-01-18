/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:34:00 by cluco             #+#    #+#             */
/*   Updated: 2022/01/18 18:34:00 by cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int ch, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (NULL);
	while ((i < n) & ((((unsigned char *)src)[i]) != (unsigned char)ch))
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	if (i >= n)
		return (NULL);
	else
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	return (&(((unsigned char *)dest)[i + 1]));
}
