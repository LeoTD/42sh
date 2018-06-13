#include "ast.h"
#include "stdio.h"
#include "_interpreter_dev.h"

char	test_output_file[200];

typedef t_ast	*node_factory(void);

void	run_basic_interpreter_list_test(node_factory **nodes,
									char *test_name, char *expect)
{
	t_ast *head, *curr;

	fprintf(stderr, "\nRunning %s \n", test_name);
	reset_ok_fail_labels();
	bzero(test_output_file, sizeof(test_output_file));
	strcat(test_output_file, test_name);
	strcat(test_output_file, ".out");
	fclose(fopen(test_output_file, "w"));
	if (!nodes)
		return ;
	head = curr = nodes[0]();
	for (int i = 1; nodes[i] != NULL; i++)
	{
		curr->rchild = nodes[i]();
		curr = curr->rchild;
	}
	interpret_tree(head);
	check_test_output(expect);
}

void	list_simple_ands_test(void)
{
	node_factory *f[] = { ok_and, ok_and, fail_and, oknode, NULL };
	run_basic_interpreter_list_test(f, "list_test_simple_ands", "OK   A, OK   B, FAIL A, ");
}

void	list_simple_ors_test(void)
{
	node_factory *f[] = { fail_or, fail_or, ok_or, fail_or, ok_or, ok_or,
		fail_or, failnode, NULL };
	run_basic_interpreter_list_test(f, "list_test_simple_ors", "FAIL A, FAIL B, OK   A, ");
}

void	list_test_mixed_with_negates(void)
{
	node_factory *f[] = { fail_or, notok_or, ok_or, notok_or, notfail_or,
		fail_and, failnode, NULL };
	run_basic_interpreter_list_test(f, "list_test_mixed_with_negates",
			"FAIL A, OK   A, OK   B, FAIL D, ");
}

void	list_hard_test(void)
{
	node_factory *f[] = { notfail_and, notok_or, ok_or, notok_sep, ok_and,
		notok_and, notfail_and, notok_or, ok_and, failnode, NULL };
	run_basic_interpreter_list_test(f, "list_hard_test",
			"FAIL A, OK   A, OK   B, OK   D, OK   E, OK   G, FAIL C, ");
}

void	list_simplest_test(void)
{
	node_factory *f[] = { oknode, NULL };
	run_basic_interpreter_list_test(f, "list_simplest_test", "OK   A, ");
}

void	pipe_helloworld_test()
{
	fprintf(stderr, "\nRunning pipe_simplest_test\n");
	char	*tok[] = { "echo", "hello", NULL };
	t_ast *c = cmd_node(tok);
	interpret_tree(c);
}

void	pipe_HELLOUNIVERSE_test()
{
	fprintf(stderr, "\nRunning pipe_HELLOUNIVERSE_test");fprintf(stderr, "\n");
	t_ast *head;
	char *tok[] = { "echo", "hello", "world", NULL };
	char *t2[] = { "tr", "a-z", "A-Z", NULL };
	char *t3[] = { "sed", "s/WORLD/UNIVERSE/", NULL };

	head = opnode(PIPE);
	head->rchild = opnode(PIPE);
	head->lchild = cmd_node(tok);
	head->rchild->lchild = cmd_node(t2);
	head->rchild->rchild = cmd_node(t3);
	interpret_tree(head);
}

void	pipe_HELLOWORLD_test()
{
	fprintf(stderr, "\nRunning pipe_HELLOWORLD_test");fprintf(stderr, "\n");
	t_ast *head;
	char *tok[] = { "echo", "hello", "world", NULL };
	char *t2[] = { "tr", "a-z", "A-Z", NULL };
	head = opnode(PIPE);
	head->lchild = cmd_node(tok);
	head->rchild = cmd_node(t2);
	interpret_tree(head);
}


void	interpret_simple_cmd(t_ast *a);

void	do_redir_test(char **tok, enum e_redirect op,
			int opt_fd, char *word, int is_fd)
{

	t_redir *r = make_redir(opt_fd, op, word, is_fd);
	examine_redir(r);
	t_list *lst = ft_lstnew(r, sizeof(*r));
	t_ast *c = cmd_node(tok);
	c->redirs = lst;
	handle_redirs(c);
	interpret_tree(c);
}

#define WRAP(function_call) if (fork() == 0) {	function_call; exit(0); } else { wait(0); }

int		main(void)
{
	char *t1[] = { "echo", "redirect testing is fun", NULL };
	char *t2[] = { "tr", "a-z", "A-Z", NULL };

	WRAP(do_redir_test(t1, APPEND, 1, "somefile", 0);)
	WRAP(do_redir_test(t2, INPUT, 0, "somefile", 0);)

	WRAP(pipe_HELLOUNIVERSE_test();)
	WRAP(list_hard_test();)

	WRAP(list_simplest_test();)
	WRAP(pipe_helloworld_test();)

	WRAP(list_simple_ands_test();)
	WRAP(pipe_HELLOWORLD_test();)

	WRAP(list_test_mixed_with_negates();)
	WRAP(list_simple_ors_test();)

	return 0;
}
