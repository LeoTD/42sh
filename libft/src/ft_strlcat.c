/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:28:02 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/28 17:16:42 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*tmp;
	int		i;
	int		n;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dstsize < dst_len + 1)
		return (src_len + dstsize);
	tmp = dst;
	while (*tmp)
		tmp++;
	i = -1;
	n = dstsize - ft_strlen(dst) - 1;
	while (++i < n && *src)
		*(tmp++) = *(src++);
	*tmp = '\0';
	return (dst_len + src_len);
}
