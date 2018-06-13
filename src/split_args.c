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
	if (!_op(*c))
		return (-1);
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
	return (-1);
}

void	skip_char(char *format, int *i, char c)
{
	if (_op(c))
		while (_op(format[*i]) && format[*i])
			(*i)++;
	else if (c == '"')
		while (format[++(*i)] != c && format[*i])
			 ;
	else if (c == ' ')
		while (format[*i] == c && format[*i])
			(*i)++;
	else
		while (!_op(format[*i]) && format[*i] != ' ' && format[*i])
			(*i)++;
			
}

char	*find_next(int *i, char *format)
{
	int		end;
	char	*tmp;

	end = 0;
	tmp = NULL;
	while (format[*i] && *i < (int)ft_strlen(format))
	{
		end = *i;
		if (format[*i] == ' ')
		{
			skip_char(format, i, ' ');
		}
		else if (is_op(format + *i) != -1)
		{
			skip_char(format, &end, format[end]);
			tmp = ft_strsub(format, *i, end - *i);
			break ;
		}
		else if (format[*i] == '"')
		{
			skip_char(format, &end, '"');
			tmp = ft_strsub(format, *i, ((end += 1) - *i));
			break ;
		}
		else
		{
			skip_char(format, &end, 'a');
			tmp = ft_strsub(format, *i, end - *i);
			break ;
 		}
		if (*i == (int)ft_strlen(format))
			return (NULL);
	}
	*i += (end - *i);
	return (tmp);
}

char	**split_args(char *format)
{
	char		**tmp;
	int			i;
	int			k;
	int			hold;
	st_init(&i, &k, &hold);
	if (!(tmp = st_strptrnew(ft_strlen(format) / 2)))
		return (0);
	while (format[i] && i < (int)ft_strlen(format))
	{
		tmp[k++] = find_next(&i, format);
		printf("I = %d, strlen = %d\n", i, (int)ft_strlen(format));
	}
	for (int x = 0; x < k; x++)
		printf("%d tmp =_%s_\n", x, tmp[x]);
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
		printf("-%s-\n", ptr[x++]);
	return (tmp);
}
*/
