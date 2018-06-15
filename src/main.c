#include "ft_sh.h"
#include "ast.h"

int			main(int argc, char **argv)
{
	char	**args;
	int		*tokens;
	t_ast	*ast;
	char		*line;

	ft_prompt_history_set_len(200);
	while (1)
	{
		line = ft_prompt("echo_sh $> ");
		ft_prompt_history_add(line);
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			break ;
		}
		if ((args = split_args(line)))
		{
			tokens = tokenize(args);
			create_tree(args, tokens, &ast, highest_prec(tokens));
			interpret_tree(ast);
		}
		free(line);
	}
	argc = 0;
	argv = 0;
	return (0);
}
