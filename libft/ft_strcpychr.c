#include "libft.h"

char	*ft_strcpychr (const char *src, char c)
{
	size_t	i;
	char	*res;
	char	ch;

	i = 0;
    while (src[i] != c)
		i++;
	if (src[i] == 0)
		return (NULL);
    if (!(res = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = -1;
	while (src[++i] != c)
		res[i] = src[i];
	res[i] = 0;
	i = 0;
	return (res);
}
