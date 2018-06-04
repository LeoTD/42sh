/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:55:02 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/23 15:40:45 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		st_getwords(char const *s, char c)
{
	int				i;
	int				k;

	i = 0;
	k = 0;
	while (*(s + i))
	{
		while (*(s + i) == c)
			i++;
		if (*(s + i) && *(s + i) != c)
			k++;
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	return (k);
}

static char		**st_strptrnew(size_t size)
{
	char			**tmp;
	unsigned int	i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		return (0);
	while (i < size + 1)
	{
		*(tmp + i) = 0;
		i++;
	}
	return (tmp);
}

static void		st_init(int *i, int *k, int *hold)
{
	*i = 0;
	*k = -1;
	*hold = 0;
}

char			**ft_strsplit(char const *s, char c)
{
	int				word_count;
	char			**tmp;
	int				i;
	int				k;
	int				hold;

	st_init(&i, &k, &hold);
	word_count = st_getwords(s, c);
	if (!(tmp = st_strptrnew(word_count)))
		return (0);
	while (*(s + i))
	{
		while (*(s + i) == c)
			i++;
		if (*(s + i) && *(s + i) != c)
		{
			hold = i;
			while (*(s + i) && *(s + i) != c)
				i++;
			if (!(*(tmp + ++k) = ft_strsub(s, hold, i - hold)))
				return (0);
		}
	}
	return (tmp);
}
