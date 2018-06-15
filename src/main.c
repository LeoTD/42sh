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
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			break ;
		}
		line = parse_line(line);
		ft_prompt_history_add(line);
		if (correct_syntax(line) == 0)
		{
			if ((args = split_args(line)))
			{
				tokens = tokenize(args);
				create_tree(args, tokens, &ast, highest_prec(tokens));
				interpret_tree(ast);
			}
		}
		else
			ft_putendl("La pendejada tiene un syntax incorrecto");
// TODO: Free more things. The tree, notably; but anything where we allocated a string needs looking at.
		free(line);
	}
	argc = 0;
	argv = 0;
	return (0);
}
