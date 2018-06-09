#include "ft_sh.h"

int			main(int argc, char **argv)
{
//	int		status;
	char	*temp;

	(void)argc;
	ft_printf("%s", "Hello 42sh!\n");
//	char *num = ft_itoa(4242);
//	printf("%s --\n", num);
//	shell_init();
//	prompt(g_shell);
//	status = 1;
//	while (status)
//	{


	temp = ft_prompt("Testing123 :D > ");
	//decipher the '\' values before going to the main execution


	printf("input |%s|\n", temp);
	printf("completing |%s|\n", parse_line(temp));
//	}

	argv = 0;
	return (0);
}
