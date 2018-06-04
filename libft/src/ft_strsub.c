/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:47:27 by ltanenba          #+#    #+#             */
/*   Updated: 2018/04/24 16:46:51 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Takes string { s }. Creates a new string of size { len }
** and copies { len } characters from { s + start }.
*/

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int		i;
	char				*tmp;

	if (!s)
		return (0);
	i = 0;
	tmp = ft_strnew(len);
	if (!tmp)
		return (0);
	while (i < len)
	{
		*(tmp + i) = *(s + start + i);
		i++;
	}
	return (tmp);
}
