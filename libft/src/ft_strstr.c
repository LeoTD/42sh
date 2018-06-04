/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 21:45:31 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/28 18:54:48 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*st_the_thing(char *h, char *n)
{
	int		i;
	int		j;
	int		k;
	int		yay;

	i = -1;
	j = -1;
	k = -1;
	yay = 0;
	while (*(h + ++i) && !yay)
	{
		if (*(h + i) == *n)
		{
			yay = 1;
			j = i;
			k = 0;
			while (*(n + k))
				if (*(n + k++) != *(h + j++))
					yay = 0;
			if (yay)
				return (h + i);
		}
	}
	return (0);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	char	*h;
	char	*n;
	int		yay;

	h = (char *)haystack;
	n = (char *)needle;
	yay = 1;
	while (*h && *n)
		yay = *h++ == *n++ ? 1 : 0;
	if (*n)
		return (0);
	if (yay)
		return ((char *)haystack);
	h = ft_strchr(haystack + 1, *needle);
	if (!h)
		return (0);
	return (st_the_thing(h, (char *)needle));
}
