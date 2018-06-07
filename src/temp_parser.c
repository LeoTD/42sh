#include "ft_sh.h"

/*
** Temporary parse function. To be replaced by full featured parser.
*/

void			parse_commands(t_shell *s, char *buf)
{
	s->temp_args = ft_strsplit(buf, ' ');
}
