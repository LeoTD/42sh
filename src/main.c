#include "ft_sh.h"

int			main(int argc, char **argv)
{
	ft_printf("%s", "Hello 42sh!\n- - - - - - -\n[ exit ]: Exits 42sh.\n");
//	char *num = ft_itoa(4242);
//	printf("%s --\n", num);
//	shell_init();
//	prompt(g_shell);
	char		*line;

	ft_prompt_history_set_len(200);
	while (1)
	{
		line = ft_prompt("echo_sh $> ");
		ft_prompt_history_add(line);
		ft_putendl(line);
		if (!ft_strcmp(line, "exit"))
			break ;
	}

	argc = 0;
	argv = 0;
	return (0);
}
