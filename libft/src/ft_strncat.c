/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:24:36 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/28 17:17:43 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = s1;
	while (*tmp)
		tmp++;
	i = -1;
	while (++i < n && *s2)
		*(tmp++) = *(s2++);
	*tmp = '\0';
	return (s1);
}
