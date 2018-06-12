#include "ft_sh.h"

char            *g_cmd_symbols[] = {
    [SEP] = ";",
    [AND] = "&&",
    [OR] = "||",
    [PIPE] = "|",
    [CMD] = NULL
};

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

// int		is_op(char *c);
int		op_len(char *c)
{
	int i;

	i = 0;
	while (c[i] && _op(c[i]))
		i++;
	return (i);
}


int is_op(char *c)
{
	if (op_len(c) == 1)
	{
		if (*c == ';' || *c == '|')
			return (*c == '|' ? PIPE : SEP);
		else
			ft_printf("sh: parse error near `%.1s'\n", c);
	}
	if (op_len(c) == 2)
	{
		if (!ft_strncmp(c, "||", 2) || !ft_strncmp(c, "&&", 2))
			return (!ft_strncmp(c, "||", 2) ? OR : AND);
		else if (ft_printf("sh: parse error near `%.2s'\n", c))
			exit(1);
	}
	else if (op_len(c) != 2)
	{
		if (op_len(c) == 3)
			ft_printf("sh: parse error near `%.1s'\n", c + 2);
		else if (op_len(c) >= 4)
			ft_printf("sh: parse error near `%.2s'\n", c + 2);
		exit(1);
	}
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
	word_count = ft_strlen(format) / 2;
	if (!(tmp = st_strptrnew(word_count)))
		return (0);
	while (format[i])
	{
		hold = i;
		while (format[i] && !_op(format[i]))
			i++;
		if (_op(format[i]))//i is where && || ; are but we also need to be looking for >> > < and ()
		{
			printf("k = .%d. i = .%d. hold = .%d.\n", k, i, hold);
			tmp[k++] = ft_strsub(format, hold, i - hold);//this copies the string into the array
			tmp[k++] = ft_strdup(g_cmd_symbols[is_op(&(format[i]))]);//this copies the operator into the array
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
