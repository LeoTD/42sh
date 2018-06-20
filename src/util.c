/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 07:57:12 by eliu              #+#    #+#             */
/*   Updated: 2018/06/20 07:57:13 by eliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdio.h>

int			ft_strspacecmp(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	while (*s1 && ft_isspace(*s1))
		++s1;
	while (*s2 && ft_isspace(*s2))
		++s2;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	while (i > 0 && ft_isspace(s1[i - 1]))
		--i;
	while (j > 0 && ft_isspace(s2[j - 1]))
		--j;
	while (i && j && *s1 == *s2)
	{
		++s1;
		++s2;
		--i;
		--j;
	}
	if (i == 0 && j == 0)
		return (0);
	if (i == 0)
		return (*s2);
	return (*s1);
}

size_t		ft_strlens(char **a, int *pcount)
{
	size_t	len;

	len = 0;
	while (*a)
	{
		len += ft_strlen(*a);
		if (pcount)
			++*pcount;
		++a;
	}
	return (len);
}

char		*ft_atos(char **a)
{
	size_t	len;
	int		count;
	char	*s;

	if (!a)
		return (ft_strdup("(null)"));
	count = 0;
	len = ft_strlens(a, &count);
	s = ft_strnew(ft_strlen("[]") + ft_strlen("'', ") * (count - 1) + len);
	ft_strcat(s, "[");
	while (*a)
	{
		ft_strcat(s, "'");
		ft_strcat(s, *a);
		ft_strcat(s, "'");
		if (*(a + 1))
			ft_strcat(s, ", ");
		++a;
	}
	ft_strcat(s, "]");
	return (s);
}

char		*ft_strjoinv(int nstr, char *sep, ...)
{
	va_list	str;
	char	*res;
	size_t	len;
	int		i;

	va_start(str, sep);
	len = 0;
	i = 0;
	while (i++ < nstr)
	{
		len += ft_strlen(va_arg(str, char *));
		len += ft_strlen(sep);
	}
	res = ft_strnew(len);
	va_start(str, sep);
	i = 0;
	while (i++ < nstr)
	{
		ft_strcat(res, va_arg(str, char *));
		ft_strcat(res, sep);
	}
	ft_bzero(res + len - ft_strlen(sep), ft_strlen(sep));
	return (res);
}

void		ft_lstaddback(t_list **lst, t_list *new)
{
	t_list	*iter;

	if (!*lst)
		*lst = new;
	else
	{
		iter = *lst;
		while (iter->next)
			iter = iter->next;
		iter->next = new;
	}
}
