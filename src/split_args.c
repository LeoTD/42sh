#include "ft_sh.h"
#include "ast.h"

int			op_error_handle(char *c)
{
	if (op_len(c) == 2)
	{
		if (!ft_strncmp(c, "||", 2) || !ft_strncmp(c, "&&", 2))
			return (!ft_strncmp(c, "||", 2) ? OR : AND);
		else if (ft_printf("sh: parse error near `%.2s'\n", c))
			return (PARSE_ERROR);
	}
	else if (op_len(c) != 2)
	{
		if (op_len(c) == 3)
			ft_printf("sh: parse error near `%.1s'\n", c + 2);
		else if (op_len(c) >= 4)
			ft_printf("sh: parse error near `%.2s'\n", c + 2);
		return (PARSE_ERROR);
	}
	return (NOT_OP);
}

int			is_op(char *c)
{
	if (!OPCHAR(*c))
		return (NOT_OP);
	if (op_len(c) == 1)
	{
		if (*c == ';' || *c == '|')
			return (*c == '|' ? PIPE : SEP);
		else if (*c == '!' && *(c + 1) == ' ')
			return (NEGATE);
		else
			ft_printf("sh: parse error near `%.1s'\n", c);
	}
	return (op_error_handle(c));
}

int			skip_char(char *format, int *i, char c)
{
	int r_count;
	int l_count;

	r_count = 0;
	l_count = 0;
	if (OPCHAR(c))
		while (OPCHAR(format[*i]) && format[*i])
			(*i)++;
	else if (c == '>')
		while (!OPCHAR(format[*i])
				&& !((r_count == 2 || l_count == 1) && REDIR_CHAR(format[*i])))
		{
			r_count += format[*i] == '>' ? 1 : 0;
			l_count += format[(*i)++] == '<' ? 1 : 0;
		}
	else if (c == '"')
		while (format[(*i) + 1] != c && format[*i])
		  (*i)++;
	else if (c == ' ')
		while (format[*i] == c && format[*i])
			(*i)++;
	else
		while (!OPCHAR(format[*i]) && format[*i] != ' ' && format[*i])
			(*i)++;
	return (1);
}

char		*find_next(int *i, char *format, int end, char *tmp)
{
	int toggle;

	while (format[*i] && *i < (int)ft_strlen(format) && !(toggle = 0))
	{
		end = *i;
		if (is_op(format + *i) == PARSE_ERROR)
			return (NULL);
		if (format[*i] == ' ')
			skip_char(format, i, ' ');
		else if (is_op(format + *i) != NOT_OP &&
				skip_char(format, &end, format[end]) && (toggle = 1))
			tmp = ft_strsub(format, *i, end - *i);
		else if (format[*i] == '"' && skip_char(format, &end, '"')
				&& (toggle = 1))
		  tmp = ft_strsub(format, (*i + 1), ((end += 1) - *i) - 1);
		else if (is_shovel(format, *i) && skip_char(format, &end, '>')
				&& (toggle = 1))
			tmp = ft_strsub(format, *i, end - *i);
		else if (skip_char(format, &end, 'a') && (toggle = 1))
			tmp = ft_strsub(format, *i, end - *i);
		if (toggle == 1)
			break ;
	}
	*i += (end - *i);
	return (tmp);
}

/*
** todo: free tmp in split_args if returning early
*/

char		**split_args(char *format)
{
	char		**tmp;
	int			i;
	int			k;
	int			hold;

	i = 0;
	k = 0;
	hold = 0;
	if (!(tmp = st_strptrnew(ft_strlen(format) / 2)))
		return (0);
	while (format[i] && i < (int)ft_strlen(format))
	{
		if (is_all_space(format, i))
			break ;
		if (!(tmp[k++] = find_next(&i, format, 0, NULL)))
			return (NULL);
	}
	tmp[k] = NULL;
	return (tmp);
}
