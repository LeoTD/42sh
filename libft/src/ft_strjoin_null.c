/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:06:53 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/22 19:10:41 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	safe_strlen(char const *str)
{
	return (!str ? 0 : ft_strlen(str));
}

char		*ft_strjoin_null(char const *s1, char const *s2)
{
	char	*tmp;
	int		len;
	int		i;

	i = -1;
	len = safe_strlen(s1) + safe_strlen(s2);
	tmp = ft_strnew(len);
	if (!tmp)
		return (0);
	while (*s1)
		*(tmp + ++i) = *(s1++);
	return (tmp);
}
