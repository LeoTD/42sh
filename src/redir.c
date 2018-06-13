#include "ast.h"
#include <unistd.h>
#include <fcntl.h>

/*
** Handling redirections for individual command nodes.
*/

static int		oflags[3] =
{
	[INPUT] = O_RDONLY,
	[TRUNC] = O_CREAT | O_TRUNC | O_WRONLY,
	[APPEND] = O_CREAT | O_APPEND | O_WRONLY,
};

int		redir_source_fd(t_redir *redir)
{
	int		fd;

	if (redir->file_string_represents_fd)
		fd = redir->from_file[1] + '0';
	else if (redir->op == INPUT)
		fd = open(redir->from_file, oflags[redir->op]);
	else
		fd = open(redir->from_file, oflags[redir->op],
				S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	return (fd);
}

void	handle_one_redir(t_redir *redir)
{
	int		from_fd;

	from_fd = redir_source_fd(redir);
	close(redir->to_fd);
	dup(from_fd);
	close(from_fd);
	return ;
}

void	handle_redirs(t_ast *a)
{
	t_list	*redirs;

	redirs = a->redirs;
	while (redirs)
	{
		handle_one_redir(redirs->content);
		redirs = redirs->next;
	}
	return ;
}
