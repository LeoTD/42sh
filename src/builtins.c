/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 21:13:12 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/05 23:36:15 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			ftsh_cd(char **args)
{
	if (args[1] == NULL)
		ft_putstr_fd("lsh: expected argument to \"cd\"\n", STDERR_FILENO);
	else 
	{
		if (chdir(args[1]) != 0)
			perror("42sh");
	}
	return (1);
}

int			ftsh_help(char **args)
{
	ft_putendl("This is 42sh!");
	ft_putendl(" - - - - - - ");
	args = 0;
	return (1);
}

int			ftsh_exit(char **args)
{
	args = 0;
	return (0);
}
