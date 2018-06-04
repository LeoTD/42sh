/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:29:28 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/22 19:19:50 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		len;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = ft_strnew(len);
	if (!tmp)
		return (0);
	while (*s1)
		*(tmp + ++i) = *(s1++);
	while (*s2)
		*(tmp + ++i) = *(s2++);
	return (tmp);
}
