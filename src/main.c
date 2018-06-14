#include "ft_sh.h"

int			main(int argc, char **argv)
{
/* // stuff that i was using for testing
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


	temp = ft_prompt("42sh> ");
	//decipher the '\' values before going to the main execution


	printf("input |%s|\n", temp);
	printf("completing |%s|\n", parse_line(temp));
//	free(temp);
*/
	char		*line;

	ft_printf("%s", "Hello 42sh!\n- - - - - - - - - -\n\nUse [ exit ] to quit echo_sh.\n\n");

/*	This function must be called to enable history.
**	Sets the max length of the history log.	*/
	ft_prompt_history_set_len(200);

	while (1)
	{
/*		ft_prompt returns [ NULL ] on error.
**		and a pointer to a fresh string on success. */
		line = ft_prompt("echo_sh $> ");

/*		This function adds a string to the history log.
**		ft_prompt does NOT keep track of history internally. */
		ft_prompt_history_add(line);

		ft_putendl(line);
		if (!ft_strcmp(line, "exit"))
		{
/*			[ line ] has been malloc'd by ft_prompt and must be freed.
**			History is freed by ft_prompt on program exit. */
			free(line);
			break ;
		}
		free(line);
	}
	return (0);
}
