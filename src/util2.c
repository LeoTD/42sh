/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 08:07:58 by eliu              #+#    #+#             */
/*   Updated: 2018/06/20 08:08:02 by eliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdio.h>

int			arr_length(char **a)
{
	int i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

void		ft_strcpy_2d(char **dst, char **src)
{
	while (*src)
		*dst++ = ft_strdup(*src++);
}

char		**ft_strdup_2d(char **src)
{
	char	**dst;

	dst = ft_memalloc((arr_length(src) + 1) * sizeof(*dst));
	ft_strcpy_2d(dst, src);
	return (dst);
}

void		ft_swap_str(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
