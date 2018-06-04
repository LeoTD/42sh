/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 15:42:16 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/28 17:15:02 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*tsr;
	size_t			i;

	i = -1;
	tmp = (unsigned char *)dst;
	tsr = (unsigned char *)src;
	while (++i < n)
		*(tmp++) = *(tsr++);
	return (dst);
}
