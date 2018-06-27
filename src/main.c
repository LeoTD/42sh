/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 07:56:40 by eliu              #+#    #+#             */
/*   Updated: 2018/06/27 01:57:28 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (i != BIN_ECHO && !ft_strcmp(args[0], g_builtin_str[i]))
		{
			g_builtins_dispatch[i](args + 1);
			return (1);
		}
		++i;
	}
	return (0);
}

char		**split_valid_line(char *line)
{
	char	**args;

	if (!ft_strspacecmp(line, "exit"))
		exit(0);
	line = parse_line(line);
	if (syntax_error(line))
	{
		ft_putendl("./42sh Invalid syntax");
		return (NULL);
	}
	else if (!(args = split_args(line)))
		return (NULL);
	free(line);
	return (args);
}

int			parse_and_interpret(char **args)
{
	t_ast	*ast;
	int		*tokens;

	ast = NULL;
	if (catch_unforkable(args))
		return (1);
	if (!(tokens = tokenize(args)))
		return (0);
	create_tree(args, tokens, &ast, highest_prec(tokens));
	if (ast)
		interpret_tree(ast);
	free(ast);
	return (1);
}

int			main(int argc, char **argv, char **environ)
{
	char	*line;
	char	**args;

	g_environ = ft_strdup_2d(environ);
	signal(SIGINT, SIG_IGN);
	if (argc > 1)
		return (parse_and_interpret(argv + 1));
	ft_prompt_history_set_len(200);
	while (1)
	{
		line = ft_prompt("42sh $> ");
		if (!ft_strlen(line) || !ft_strspacecmp(line, ""))
			continue ;
		ft_prompt_history_add(line);
		if (!(args = split_valid_line(line)) || !(parse_and_interpret(args)))
			ft_putstr_fd("Parse error\n", 2);
	}
	return (0);
}
