#ifndef AST_H
# define AST_H
# include "libft.h"

/*
** Possible types for AST nodes.
** sep		and		or		negate	pipe	cmd
** ;		&&		||		!		|		simple command, eg ">2 cat <file"
*/

typedef enum	e_cmdtype
{
	CMD,
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
}				t_ast;

extern char		*g_cmd_symbols[MAX_CMDTYPE + 1];
extern char		*g_cmd_names[MAX_CMDTYPE + 1];

t_ast			*ast_node(void);
t_ast			*opnode(t_cmdtype type);
t_ast			*cmd_node(char **tokens);
t_ast			*quick_cmd_node(char *s1, char *s2, char *s3);

#endif
