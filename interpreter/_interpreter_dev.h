#ifndef _INTERPRETER_DEV_H
# define _INTERPRETER_DEV_H
# include "ast.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

extern char test_output_file[200];

t_ast	*oknode();
t_ast	*failnode();
void	reset_ok_fail_labels();

t_ast	*ok_or();
t_ast	*fail_and();
t_ast	*fail_or();
t_ast	*ok_and();
t_ast	*ok_sep();
t_ast	*fail_sep();

t_ast	*notok_or();
t_ast	*notfail_and();
t_ast	*notfail_or();
t_ast	*notok_and();
t_ast	*notok_sep();
t_ast	*notfail_sep();

void	print_tokens(char **tokens);
void	print_node(t_ast *a);
void	print_pipe(int fd[2]);
void	examine_tree(t_ast *a);

int		check_test_output(char *expected_str);

void	run_interpreter_tests(void);
#endif
