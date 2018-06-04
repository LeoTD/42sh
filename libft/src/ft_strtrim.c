/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:28:21 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/23 00:07:29 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_trimlen(char const *s)
{
	int		i;
	int		len;

	len = 0;
	i = -1;
	while (*s && ft_isspace(*s))
		s++;
	while (*(s + ++i))
		len++;
	while (ft_isspace(*(s + len - 1)) && len > 0)
		len--;
	return (len);
}

char		*ft_strtrim(char const *s)
{
	char	*tmp;
	int		i;
	int		len;

	if (!s)
		return (0);
	i = -1;
	len = ft_trimlen(s);
	tmp = ft_strnew(len);
	if (!tmp)
		return (0);
	while (*s && ft_isspace(*s))
		s++;
	while (*s && ++i < len)
		*(tmp + i) = *(s++);
	return (tmp);
}
