#include "ft_sh.h"

int			main(int argc, char **argv)
{
	ft_printf("%s", "Hello 42sh!\n");
//	char *num = ft_itoa(4242);
//	printf("%s --\n", num);
//	shell_init();
//	prompt(g_shell);
	ft_prompt("Testing123 :D > ");

	argc = 0;
	argv = 0;
	return (0);
}
