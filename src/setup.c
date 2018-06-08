#include "ft_sh.h"

void		term_init(t_term *t)
{
	t->name = getenv("TERM");
	t->fd = open("/dev/tty", O_RDWR);
	tgetent(0, t->name);
	tcgetattr(TERM_FD, &t->normal);
	tcgetattr(TERM_FD, &t->custom);
	t->custom.c_lflag |= ICANON;
	t->custom.c_lflag |= ECHOE;
	t->custom.c_lflag |= ECHOK;
	t->custom.c_cc[VMIN] = 1;
	t->custom.c_cc[VTIME] = 0;
	tcsetattr(TERM_FD, TCSANOW, &t->custom);
	_term_do("ti");
	_term_do("vs");
	update_size(t);
}

void		shell_init(void)
{
	g_shell = &g_shellinit;
	term_init(&g_shell->term);
	g_shell->prompt_string = ft_strdup("marvin");

	
}

t_proc		*process_init(void)
{
	t_proc	*proc;

	proc = (t_proc *)malloc(sizeof(t_proc));
	proc->next = NULL;
	proc->argv = NULL;
	proc->pid = 0;
	proc->is_pipe = 0;
	proc->completed = 0;
	proc->stopped = 0;
	proc->status = 0;
	return (proc);
}

t_job		*job_init(void)
{
	t_job	*job;

	job = (t_job *)malloc(sizeof(t_job));
	job->next = NULL;
	job->prev = NULL;
	ft_bzero(&job->tmodes, sizeof(job->tmodes));
	job->s_in = 0;
	job->s_out = 0;
	job->s_err = 0;
	job->first_process = NULL;
	job->command = 0;
	job->notified = 0;
	job->pgid = 0;
	return (job);
}
