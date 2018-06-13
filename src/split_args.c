#include "ft_sh.h"

char		*g_cmd_symbols[] = {
    [SEP] = ";",
    [AND] = "&&",
    [OR] = "||",
    [PIPE] = "|",
    [CMD] = NULL
};

int 		is_op(char *c)
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

int			skip_char(char *format, int *i, char c)
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
	return (1);
}

char		*find_next(int *i, char *format, int end, char *tmp)
{
	while (format[*i] && *i < (int)ft_strlen(format))
	{
		end = *i;
		if (format[*i] == ' ')
			skip_char(format, i, ' ');
		else if (is_op(format + *i) != -1 && skip_char(format, &end, format[end]))
		{
			tmp = ft_strsub(format, *i, end - *i);
			break ;
		}
		else if (format[*i] == '"' && skip_char(format, &end, '"'))
		{
			tmp = ft_strsub(format, *i, ((end += 1) - *i));
			break ;
		}
		else if (skip_char(format, &end, 'a'))
		{
			tmp = ft_strsub(format, *i, end - *i);
			break ;
 		}
		if (*i == (int)ft_strlen(format))
			return (NULL);
	}
	*i += (end - *i);
	return (tmp);
}

char		**split_args(char *format)
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
		if (is_all_space(format, i))
			break ;
		tmp[k++] = find_next(&i, format, 0, NULL);
	}
//	for (int x = 0; x < k; x++)
//		printf("%d tmp =_%s_\n", x, tmp[x]);
	return (tmp);
}
