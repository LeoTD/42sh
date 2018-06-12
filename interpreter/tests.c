#include "ast.h"
#include "stdio.h"
#include "_interpreter_dev.h"

char	test_output_file[200];

typedef t_ast	*node_factory(void);

void	run_basic_interpreter_test(node_factory **nodes,
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

void	simple_ands(void)
{
	node_factory *f[] = { ok_and, ok_and, fail_and, oknode, NULL };
	run_basic_interpreter_test(f, "simple_ands", "OK   A, OK   B, FAIL A, ");
}

void	simple_ors(void)
{
	node_factory *f[] = { fail_or, fail_or, ok_or, fail_or, ok_or, ok_or,
		fail_or, failnode, NULL };
	run_basic_interpreter_test(f, "simple_ors", "FAIL A, FAIL B, OK   A, ");
}

void	mixed_with_negates(void)
{
	node_factory *f[] = { fail_or, notok_or, ok_or, notok_or, notfail_or,
		fail_and, failnode, NULL };
	run_basic_interpreter_test(f, "mixed_with_negates",
			"FAIL A, OK   A, OK   B, FAIL D, ");
}

void	hard_test(void)
{
	node_factory *f[] = { notfail_and, notok_or, ok_or, notok_sep, ok_and,
		notok_and, notfail_and, notok_or, ok_and, failnode, NULL };
	run_basic_interpreter_test(f, "hard_test",
			"FAIL A, OK   A, OK   B, OK   D, OK   E, OK   G, FAIL C, ");
}

void	simplest_test(void)
{
	node_factory *f[] = { oknode, NULL };
	run_basic_interpreter_test(f, "simplest_test", "OK   A, ");
}

int		main(void)
{
	simple_ands();
	hard_test();
	mixed_with_negates();
	simple_ors();
	return 0;
}
