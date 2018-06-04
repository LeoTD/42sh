/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:25:04 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/23 00:00:38 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *z, int y, size_t len)
{
	unsigned char	c;
	unsigned char	*tmp;
	unsigned int	i;

	i = 0;
	c = y;
	tmp = (unsigned char *)z;
	while (i < len)
	{
		*(tmp + i) = c;
		i++;
	}
	return (z);
}
