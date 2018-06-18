#include "libft.h"

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
