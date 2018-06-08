/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 12:24:30 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/08 01:07:02 by gmalpart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			main(int argc, char **argv)
{
	char **args;
	char **second;

	if (argc == 2)
	{
//		ft_printf("%s", "Hello 42sh!\n");
		args = split_args(argv[1]);
		printf("end of old one\n");
		second =  tokenizer(argv[1]);
	}
//	shell_init();
//	prompt(g_shell);
	argv = 0;
	return (0);
}
