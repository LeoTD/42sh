#include "ft_sh.h"
#include "ast.h"
//#include <crt_externs.h>

/*
** TODO:
** todo1 free strings and tree
** todo2 pick split_args error message
*/

char		**g_environ;

void		parse_and_interpret(char **args)
{
	t_ast	*ast;
	int		*tokens;

	ast = NULL;
	if (!(tokens = tokenize(args)))
		return ;
	create_tree(args, tokens, &ast, highest_prec(tokens));
	if (ast)
		interpret_tree(ast);
	free(ast);
	free(tokens);
}

int			main(int argc, char **argv, char **environ)
{
	char	**args;
	char	*line;

	g_environ = environ;
	ft_prompt_history_set_len(200);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		line = ft_prompt("echo_sh $> ");
		if (!ft_strcmp(line, "exit"))
			exit(0);
		line = parse_line(line);
		ft_prompt_history_add(line);
		if (syntax_error(line))
		{
			ft_putendl("La pendejada tiene un syntax incorrecto");
			sleep(1);
		}
		else if (!(args = split_args(line)))
			;
		else
			parse_and_interpret(args);
		free(line);
	}
	argc = 0;
	argv = 0;
	return (0);
}
