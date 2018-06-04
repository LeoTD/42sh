/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 17:32:37 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/26 16:07:57 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp;
	size_t			i;

	i = -1;
	tmp = (unsigned char *)dst;
	while (++i < len)
	{
		if (dst < src)
			*(tmp + i) = *((unsigned char *)src + i);
		else
			*(tmp + (len - i - 1)) = *((unsigned char *)src + (len - i - 1));
	}
	return (dst);
}
