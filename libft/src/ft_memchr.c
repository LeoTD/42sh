/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:09:01 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/26 16:23:08 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	void		*ret;

	ret = (void *)s;
	i = -1;
	while (++i < n)
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return (ret + i);
	return (0);
}
