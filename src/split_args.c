#include "ft_sh.h"
#include "ast.h"

int 		is_op(char *c)
{
	if (!_op(*c))
		return (-1);
	if (op_len(c) == 1)
	{
		if (*c == ';' || *c == '|' || *c == '!')
		{
		 	if (*c == '|')
			 return (PIPE);
			else if (*c == '!')
				return (*c == NEGATE);
			else if (*c == ';')
				return (SEP);
		}
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
	int r_count;
	int l_count;

	if (_op(c))
		while (_op(format[*i]) && format[*i])
			(*i)++;
	else if (c == '>' && !(r_count = 0) && !(l_count = 0))
	{
		while (!_op(format[*i]) && !((r_count == 2 || l_count == 1) && _redir(format[*i])))
		{
			r_count += format[*i] == '>' ? 1 : 0;
			l_count += format[(*i)++] == '<' ? 1 : 0;
		}
	}
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
	int toggle;

	while (format[*i] && *i < (int)ft_strlen(format))
	{
		toggle = 0;
		end = *i;
		if (format[*i] == ' ')
			skip_char(format, i, ' ');
		else if (is_op(format + *i) != -1 &&
				skip_char(format, &end, format[end]) && (toggle = 1))
			tmp = ft_strsub(format, *i, end - *i);
		else if (format[*i] == '"' && skip_char(format, &end, '"') && (toggle = 1))
			tmp = ft_strsub(format, *i, ((end += 1) - *i));
		else if (is_shovel(format, *i) && skip_char(format, &end, '>')
				&& (toggle = 1))
				tmp = ft_strsub(format, *i, end - *i);
		else if (skip_char(format, &end, 'a') && (toggle = 1))
			tmp = ft_strsub(format, *i, end - *i);
		if (toggle == 1)
			break;
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
	tmp[k] = NULL;
	return (tmp);
}
