/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 22:23:32 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/05 23:32:56 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			launch(char **args)
{
	pid_t		pid;
	pid_t		wpid;
	int			status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("42sh");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("42sh");
	else
		wpid = waitpid(pid, &status, WUNTRACED);
	return (1);
}

int			execute(char **args)
{
	int			id;

	if (args[0] == 0)
		return (1);
	id = -1;
	if ((id = is_builtin(args[0])) != -1)
		return (run_builtin(id, args));
	return (launch(args));
}

void		prompt(t_shell *s)
{
	char		*buf;
	char		status;

	status = 1;
	while (status)
	{
		ft_printf("%s$>", s->prompt_string);
		get_next_line(1, &buf);
		parse_commands(s, buf);
		status = execute(s->temp_args);
	}
	restore_defaults(&s->term);
}
