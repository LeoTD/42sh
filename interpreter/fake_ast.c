#include "ft_sh.h"
#include "ast.h"

void	print_tokens(char **tokens);

t_ast	*fake_ast()
{
	t_ast *head;

	head = opnode(PIPE);
	head->lchild = quick_cmd_node("echo", "hello", "world");
	head->rchild = opnode(PIPE);
	head->rchild->lchild = quick_cmd_node("sed", "s/ell/ELL/", NULL);
	head->rchild->rchild = quick_cmd_node("tr", "E", "X");
	return head;
}
