/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyuntil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:53:24 by ltanenba          #+#    #+#             */
/*   Updated: 2018/03/30 21:35:12 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the index of the char "c" in string dst.
*/

int			ft_copyuntil(char **dst, char *src, char c)
{
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (src[++i])
		if (src[i] == c)
			break ;
	if (!(*dst = ft_strnew(i)))
		return (0);
	while (src[k] && k < i)
	{
		*(*dst + k) = *(src + k);
		k++;
	}
	return (i);
}
