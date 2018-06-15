#ifndef AST_H
# define AST_H
# include "libft.h"

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

typedef enum					e_cmdname
{
	ECH,
	CD,
	EXIT,
	ENV,
	SETENV,
	UNSETENV,
	END
}								t_cmdname;

typedef struct	s_ast
{
	char			**tokens;
	struct s_ast	*lchild;
	struct s_ast	*rchild;
	int				type;
	int				ok;
	t_list			*redirs;
}				t_ast;

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
extern char		*g_nodetype_names[MAX_CMDTYPE + 1];

t_ast			*parsed_ast_node(char **args, int *tokens, int hp);
int				highest_prec(int *tokens);
void			print_tree(t_ast *ast, int i, int lr);
void			create_tree(char **args, int *tokens, t_ast **head, int hp);
t_ast			*ast_node(void);
t_ast			*opnode(t_cmdtype type);
t_ast			*cmd_node(char **tokens);

void			interpret_tree(t_ast *tree);
void			handle_redirs(t_ast *leaf);

t_redir			*new_redir(void);
void			env_exec(t_ast *a);

#endif
