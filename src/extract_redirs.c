#include "ft_sh.h"

int	g_oflags[3] =
{
	[INPUT] = O_RDONLY,
	[TRUNC] = O_CREAT | O_TRUNC | O_WRONLY,
	[APPEND] = O_CREAT | O_APPEND | O_WRONLY,
};

t_redir			*new_redir(void)
{
	return ((t_redir *)ft_memalloc(sizeof(t_redir)));
}

t_redir			*new_full_redir(int left, enum e_redirect op, char *right,
		int is_fd)
{
	t_redir *r;

	r = new_redir();
	r->to_fd = left;
	r->op = op;
	r->from_file = ft_strdup(right);
	r->file_string_represents_fd = is_fd;
	return (r);
}

void			append_redir(t_ast *a, t_redir *r)
{
	t_list	*lst;

	lst = ft_lstnew(r, sizeof(*r));
	ft_lstaddback(&(a->redirs), lst);
}

static t_redir	*get_redir_match(char *s)
{
	char	*redir_start;
	t_redir	*r;

	if (!(redir_start = ft_strchr(s, '>'))
			&& !(redir_start = ft_strchr(s, '<')))
		return (NULL);
	if (!(ft_strchr("1234567890 \t", *(redir_start - 1))))
		return (NULL);
	r = new_redir();
	if (*redir_start == '<')
		r->op = INPUT;
	else if (*(redir_start + 1) == '>')
		r->op = APPEND;
	else
		r->op = TRUNC;
	if (ft_isdigit(*(redir_start - 1)))
		r->to_fd = *(redir_start - 1) - '0';
	else
		r->to_fd = r->op != INPUT;
	r->from_file = redir_start + 1 + (r->op == APPEND);
	while (ft_isspace(r->from_file[0]))
		++r->from_file;
	r->file_string_represents_fd = (r->from_file[0] == '&'
			&& ft_isdigit(r->from_file[1])
			&& (ft_isspace(r->from_file[2]) || r->from_file[2] == '\0'));
	return (r);
}

void			extract_redirs(t_ast *a)
{
	char	**cmd;
	char	**filtered;
	int		i;
	t_redir	*r;

	cmd = a->tokens;
	filtered = ft_memalloc((arr_length(cmd) + 1) * sizeof(*cmd));
	i = 0;
	while (*cmd)
	{
		if ((r = get_redir_match(*cmd)))
			append_redir(a, r);
		else
		{
			filtered[i] = ft_strdup(*cmd);
			++i;
		}
		++cmd;
	}
	a->tokens = filtered;
}
