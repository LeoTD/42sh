#include "ft_sh.h"

int		highest_prec(int *tokens, int len)
{
	int i;

	i = -1;
	while (++i < len)
		if (tokens[i] < 3)
			return (i);
	i = -1;
	while (++i < len)
		if (tokens[i] < 4)
			return (i);
	return (-1);
}

t_ast	*create_tree(char **args, int *tokens, t_ast *head)
{
	int i;

	i = highest_prec(tokens, arr_length(args));
	printf("%d\n", i);
	if (!head)
		head = ast_init();
//	if (_op(tokens[i]))
//	{
//		
//	}
	return (head);
}
