#include "ft_sh.h"
#include "ast.h"

char	*g_commands[] = {
	[ECH] = "echo",
	[CD] = "cd",
	[EXIT] = "exit",
	[ENV] = "env",
	[SETENV] = "setenv",
	[UNSETENV] = "unsetenv",
	[END] = "end"
};

char	*g_nodetype_names[] = {
	[SEP] = ";",
	[AND] = "&&",
	[OR] = "||",
	[PIPE] = "|",
	[NEGATE] = "!",
	[CMD] = NULL
};

int		arr_length(char **format)
{
	int i;

	i = 0;
	while (format[i])
		i++;
	return (i);
}

int		is_command(char *arg)
{
	int i;

	i = 0;
	while (g_commands[i])
	{
		if (!ft_strcmp(arg, g_commands[i]))
			return (1);
		i++;
	}
	return (-1);
}

int		is_operator(char *arg)
{
	int i;

	i = 0;
	while (i <= MAX_CMDTYPE)
	{
		if (g_nodetype_names[i] && !ft_strcmp(arg, g_nodetype_names[i]))
			return (i);
		i++;
	}
	return (-1);
}

int		*tokenize(char **format)
{
	int *token;
	int i;

	i = 0;
	if (!(token = (int *)malloc(sizeof(int) * arr_length(format))))
		return (NULL);
	ft_bzero(token, arr_length(format));
	while (i < arr_length(format))
	{
		if (is_command(format[i]) >= 0)
			token[i] = is_command(format[i]);
		else if (is_operator(format[i]) != -1)
			token[i] = is_operator(format[i]);
		else
			token[i] = CMD;
		i++;
	}
	return (token);
}
