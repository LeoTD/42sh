#include "libft.h"
#include <stdarg.h>

int			ft_strspacecmp(char *s1, char *s2)
{
	int	i;
	int	j;

	while (ft_isspace(*s1))
		++s1;
	while (ft_isspace(*s2))
		++s2;
	i = 0;
	while (!(ft_isspace(s1[i])))
		++i;
	j = 0;
	while (!(ft_isspace(s2[j])))
		++j;
	if (i < j)
		return (ft_strncmp(s1, s2, i));
	return (ft_strncmp(s1, s2, j));
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

int			arr_length(char **a)
{
	int i;

	i = 0;
	while (a[i])
		i++;
	return (i);
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

void		ft_strcpy_2d(char **dst, char **src)
{
	while (*src)
		*dst++ = ft_strdup(*src++);
}

char		**ft_strdup_2d(char **src)
{
	char	**dst;

	dst = ft_memalloc((arr_length(src) + 1) * sizeof(*dst));
	ft_strcpy_2d(dst, src);
	return (dst);
}
