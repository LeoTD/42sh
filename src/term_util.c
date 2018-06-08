#include "ft_sh.h"

int				ft_weirdchar(int c)
{
	write(TERM_FD, &c, 1);
	return (0);
}

void			update_size(t_term *t)
{
	struct winsize		w;

	ioctl(0, TIOCGWINSZ, &w);
    t->height = w.ws_row;
    t->width = w.ws_col;
}

void			restore_defaults(t_term *t)
{
	tcsetattr(TERM_FD, TCSANOW, &t->normal);
	_term_do("ve");
	_term_do("te");
}
