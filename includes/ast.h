#ifndef AST_H
# define AST_H
# include "libft.h"
# include "ft_sh.h"

/*
** Possible types for AST nodes.
** sep		and		or		negate	pipe	cmd
** ;		&&		||		!		|		simple command, eg ">&2 cat <file"
*/

typedef enum	e_cmdtype
{
	CMD = 1,
	PIPE,
	NEGATE,
	OR,
	AND,
	SEP
}				t_cmdtype;

# define LIST_PRECEDENCE OR
# define MAX_CMDTYPE SEP

typedef struct	s_ast
{
	char			**tokens;
	struct s_ast	*lchild;
	struct s_ast	*rchild;
	t_cmdtype		type;
	int				ok;
	t_list			*redirs;
}				t_ast;

/*
** POSIX standard redirect types.
** pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_07
**	in	trunc	append	noclobber	heredoc		in_dup	out_dup		rdwr
**	<	>		>>		|>			<< or <<-	&<		&>			<>
*/

/*
** We currently handle only INPUT, OUTPUT, and APPEND.
*/

enum			e_redirect
{
	INPUT,
	TRUNC,
	APPEND,
};

typedef struct	s_redir
{
	enum e_redirect		op;
	int					to_fd;
	char				*from_file;
	int					file_string_represents_fd;
}				t_redir;

extern char		*g_cmd_symbols[MAX_CMDTYPE + 1];
extern char		*g_cmd_names[MAX_CMDTYPE + 1];

t_ast			*ast_node(void);
t_ast			*opnode(t_cmdtype type);
t_ast			*cmd_node(char **tokens);

void			interpret_tree(t_ast *tree);
void			handle_redirs(t_ast *leaf);

t_redir			*new_redir(void);
t_redir			*quick_redir(int to_fd, enum e_redirect op,
		char *from, int is_fd);
void			append_redir(int to_fd, enum e_redirect op,
		char *from, int is_fd, t_ast *a);

#endif
