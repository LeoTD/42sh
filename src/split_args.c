#include "ft_sh.h"

char            *g_cmd_symbols[] = {
    [SEP] = ";",
    [AND] = "&&",
    [OR] = "||",
    [PIPE] = "|",
    [CMD] = NULL
};

static int	ft_getwords(char const *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			k++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (k);
}

static char	**st_strptrnew(size_t size)
{
	char			**tmp;
	unsigned int	i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		return (0);
	while (i < size + 1)
	{
		*(tmp + i) = 0;
		i++;
	}
	return (tmp);
}

static void	st_init(int *i, int *k, int *hold)
{
	*i = 0;
	*k = 0;
	*hold = 0;
}

int		is_op(char *c);
int		op_len(char *c)
{
	int i;

	i = 0;
	while (c[i] && _op(c[i]))
		i++;
	return (i);
}

int		is_op(char *c)
{
	if (op_len(c) == 1)
		return (*c == '|' ? PIPE : SEP);
	else if (op_len(c) == 2)
		return (*c == '&' ? AND : OR);
	else
		return (0);
}

char	**split_args(char *format)
{
	int			word_count;
	char		**tmp;
	int			i;
	int			k;
	int			hold;

	st_init(&i, &k, &hold);
	word_count = ft_getwords(format, 32);
	if (!(tmp = st_strptrnew(word_count)))
		return (0);
	while (format[i])
	{
		hold = i;
		while (format[i] && !_op(format[i]))
			i++;
		if (_op(format[i]))
		{
			tmp[k++] = ft_strsub(format, hold, i - hold);
			tmp[k++] = ft_strdup(g_cmd_symbols[is_op(&(format[i]))]);
			while (format[i] && _op(format[i]))
				i++;
		}
		else
		{
			tmp[k++] = ft_strsub(format, hold, i - hold);
		}
	}
	tmp[k] = NULL;
	int x = 0;
	while (tmp[x])
		ft_putendl(tmp[x++]);
	return (tmp);
}
/*
char	**split_args(char *format)
{
	int			word_count;
	char		**tmp;
	int			i;
	int			k;
	int			hold;

	st_init(&i, &k, &hold);
	word_count = ft_getwords(format, 32);
	if (!(tmp = st_strptrnew(word_count)))
		return (0);
	while (format[i] && i < (int)ft_strlen(format))
	{
		hold = i;
		while (format[i] && !is_op(&(format[i])))
			i++;
		if (format[i] && is_op(&(format[i])) > 0)
		{
//			fprintf(stderr, "%d %d %s\n", hold, i, ft_strsub(format, hold, i - hold));
			if (i != 0)
				tmp[k++] = ft_strsub(format, hold, i - hold);
			tmp[k++] = ft_strdup(g_cmd_symbols[is_op(&(format[i])) - 1]);
			i += (op_len(&(format[i])));
		}
		else
		{
			tmp[k++] = ft_strsub(format, hold, i - hold);
			i++;
		}
//		printf("here= %s k = %d i = %d hold = %d\n", tmp[0], k, i, hold);
	}
	tmp[k] = NULL;
	int x = 0;
	ft_putendl(tmp[0]);
	while (tmp[x])
		ft_putendl(tmp[x++]);
	return (tmp);
	}*/
/*
int		find_next(char *format, int *i)
{
	char	len;

	len = 0;
	while (format[*i])
	{
		if (format[*i] == '"')
		{
			while (format[++(*i)] != '"' && format[*i])
				len++;
			if (format[*i] == '"')
				len++;
		}
		if (ft_isspace(format[*i]))
			break ;
		len++;
		(*i)++;
	}
	return (len);
}

char	**split_args(char *format)
{
	char	**res;
	int		len;
	int		tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!(res = (char **)malloc(sizeof(char *) * ft_getwords(format, ' '))))
		return (NULL);
	while (format[i])
	{
		tmp = i;
		len = find_next(format, &i);
		res[k] = ft_strdup(ft_strsub(format, tmp, len));
		if (ft_isspace(format[i]))
			i++;
		printf("%s\n", res[k]);
		k++;
	}
	return (res);
}

char	**group_args(char **args)
{
	char	**res;
	int		i;
	
}
*/
