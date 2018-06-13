#include "ast.h"
#include "stdio.h"
#include "_interpreter_dev.h"

char	test_output_file[200];

typedef t_ast	*node_factory(void);

void	run_basic_interpreter_list_test(node_factory **nodes,
									char *test_name, char *expect)
{
	t_ast *head, *curr;

	fprintf(stderr, "Running %s \n", test_name);
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
	fprintf(stderr, "Running simplest test\n");
	char	*tok[] = { "echo", "hello", NULL };
	t_ast *c = cmd_node(tok);
	interpret_tree(c);
}

void	pipe_HELLOUNIVERSE_test()
{
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
	t_ast *head;
	char *tok[] = { "echo", "hello", "world", NULL };
	char *t2[] = { "tr", "a-z", "A-Z", NULL };
	head = opnode(PIPE);
	head->lchild = cmd_node(tok);
	head->rchild = cmd_node(t2);
	interpret_tree(head);
}


int		main(void)
{
	list_simplest_test();
//	list_simple_ands_test();
//	list_hard_test();
//	list_test_mixed_with_negates();
//	list_simple_ors_test();

	pipe_helloworld_test();
//	pipe_HELLOWORLD_test();
//	FIXME: It seems impossible to run any other test after a pipe test, at the moment. Does that make sense?
//	pipe_HELLOUNIVERSE_test();
	return 0;
}
