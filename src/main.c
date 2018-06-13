/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 12:24:30 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/12 20:38:30 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			main(int argc, char **argv)
{
	char	**args;
	int		*tokens;
	t_ast	*ast;

	if (argc == 2)
	{
		ft_printf("%s", "Hello 42sh!\n");
		args = split_args(argv[1]);
		tokens = tokenize(args);
		ast = create_tree(args, tokens, NULL);
	}
//	shell_init();
//	prompt(g_shell);
	argv = 0;
	return (0);
}
