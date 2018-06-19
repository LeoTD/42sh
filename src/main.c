#include "ft_sh.h"
#include "ast.h"
#include <crt_externs.h>

/*
** TODO:
** todo1 free strings and tree
** todo2 pick split_args error message
** todo better exit: handle `false || exit && echo hi`
*/

char		**g_environ;

int			catch_unforkable(char **args)
{
	int		i;

	i = 0;
	while (i < NUM_HANDLED_BUILTINS)
	{
		if (i != BIN_ECHO && i != BIN_ENV
				&& !ft_strcmp(args[0], g_builtin_str[i]))
		{
			g_builtins_dispatch[i](args + 1);
			return (1);
		}
		++i;
	}
	return (0);
}

void		parse_and_interpret(char **args)
{
	t_ast	*ast;
	int		*tokens;

	ast = NULL;

	if (catch_unforkable(args))
		return ;
	if (!(tokens = tokenize(args)))
		return ;
	create_tree(args, tokens, &ast, highest_prec(tokens));
	if (ast)
		interpret_tree(ast);
	free(ast);
}

int			main(int argc, char **argv, char **environ)
{
	char	**args;
	char	*line;

	g_environ = ft_strdup_2d(environ);
	ft_prompt_history_set_len(200);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		line = ft_prompt("echo_sh $> ");
		if (!ft_strspacecmp(line, "exit"))
			exit(0);
		line = parse_line(line);
		ft_prompt_history_add(line);
		if (syntax_error(line))
			ft_putendl("La pendejada tiene un syntax incorrecto");
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
