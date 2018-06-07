#include "ft_sh.h"

int			main(int argc, char **argv)
{
	ft_printf("%s", "Hello 42sh!\n");
	shell_init();
	prompt(g_shell);

	argc = 0;
	argv = 0;
	return (0);
}
