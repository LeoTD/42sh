#include "ft_sh.h"

t_ast	*ast_node();
void	print_tokens(char **tokens);

t_ast	*_ast_node(t_cmdtype ctype, char *tok1, char *tok2, char *tok3)
{
	t_ast *a = ast_node();
	char **tokens = ft_memalloc(sizeof(*tokens) * 4);
	if (tok1) tokens[0] = ft_strdup(tok1);
	if (tok2) tokens[1] = ft_strdup(tok2);
	if (tok3) tokens[2] = ft_strdup(tok3);
	a->tokens = tokens;
	a->type = ctype;
	return a;
}

t_ast	*and_node()
{
	return _ast_node(AND, "&&", NULL, NULL);
}

t_ast	*or_node()
{
	return _ast_node(OR, "||", NULL, NULL);
}

t_ast	*sep_node()
{
	return _ast_node(SEP, ";", NULL, NULL);
}

t_ast	*pipe_node()
{
	return _ast_node(PIPE, "|", NULL, NULL);
}

t_ast	*cmd_node(char *tok1, char *tok2, char *tok3)
{
	return _ast_node(CMD, tok1, tok2, tok3);
}

t_ast	*negate_node()
{
	return _ast_node(NEGATE, "!", NULL, NULL);
}

t_ast	*fake_ast()
{
	t_ast *head;

	head = or_node();
	head->lchild = pipe_node();
	head->lchild->lchild = cmd_node("echo", "hello", NULL);
	head->lchild->rchild = cmd_node("sed", "s/ell/ELL/", NULL);
	head->rchild = and_node();
	head->rchild->lchild = cmd_node("grep", "notfound", NULL);
	head->rchild->rchild = cmd_node("echo", ":(", NULL);
	return head;
}
