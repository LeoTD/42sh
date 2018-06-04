/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 12:14:39 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/23 00:05:27 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char				*tmp;
	unsigned int		i;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * size);
	if (!tmp)
		return (0);
	while (i < size)
	{
		*(tmp + i) = 0;
		i++;
	}
	return ((void *)tmp);
}
