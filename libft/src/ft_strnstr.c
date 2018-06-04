/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 22:16:44 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/28 23:26:14 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*st_the_thing(char *h, char *n, size_t len)
{
	int		i;
	int		j;
	int		k;
	int		ok;

	i = -1;
	j = -1;
	k = -1;
	ok = 1;
	while (*(h + ++i) && (size_t)i < len)
	{
		j = 0;
		if (*(h + i) == *n)
		{
			ok = 1;
			k = i;
			while (*(h + k) && *(n + j) && (size_t)j < len && (size_t)k < len)
				if (*(h + k++) != *(n + j++))
					ok = 0;
			if (ok && !*(n + j))
				return ((char *)h + i);
		}
	}
	return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	int		ok;
	int		l;

	l = len;
	h = (char *)haystack;
	n = (char *)needle;
	ok = 1;
	while (*h && *n && l-- > 0)
		if (*h++ != *n++)
			ok = 0;
	if (*n)
		return (0);
	if (ok)
		return ((char *)haystack);
	h = ft_strchr(haystack + 1, (int)*needle);
	if (!h || (size_t)(h - haystack) >= len)
		return (0);
	return (st_the_thing(h, (char *)needle, len - (h - haystack)));
}
