#include "ast.h"
#include "_interpreter_dev.h"

enum			okstate { OK, FAIL };
static char		_ok_label[] = 	"OK   A, ";
static char		_fail_label[] = "FAIL A, ";
char			write_and_exit[] = "./helpers/write_and_exit";

static char		*get_label(int reset, enum okstate which)
{
	static char		c[2] = { 'A', 'A' };
	char			*lab;

	if (reset)
	{
		c[0] = c[1] = 'A';
		return NULL;
	}
	if (which == OK)
		lab = ft_strdup(_ok_label);
	else
		lab = ft_strdup(_fail_label);
	lab[5] = c[which];
	++c[which];
	return (lab);
}

static char		*ok_label(int reset)
{
	return get_label(reset, OK);
}

static char		*fail_label(int reset)
{
	return get_label(reset, FAIL);
}

void			reset_ok_fail_labels(void)
{
	ok_label(1);
	fail_label(1);
}

t_ast			*write_and_exit_node(char *label, char *rval)
{
	char *out = NULL;
	out = ft_strnew(ft_strlen("--out=") + ft_strlen(test_output_file));
	ft_strcat(out, "--out=");
	ft_strcat(out, test_output_file);
	char **args = ft_memalloc(6 * sizeof(char *));
	args[0] = write_and_exit;
	args[1] = out;
	args[2] = "--sleep=0";
	args[3] = label;
	args[4] = rval;
	return (cmd_node(args));
}

t_ast			*oknode(void)
{
	return write_and_exit_node(ok_label(0), "0");
}

t_ast			*failnode(void)
{
	return write_and_exit_node(fail_label(0), "1");
}

static			t_ast *booljunc(enum okstate k, t_cmdtype type, int negate)
{
	t_ast *a = opnode(type);
	t_ast *head = a;
	t_ast *boolnode = (k == OK ? oknode() : failnode());
	if (negate)
	{
		a->lchild = opnode(NEGATE);
		a->lchild->rchild = boolnode;
	}
	else
		a->lchild = boolnode;
	return head;
}

t_ast			*ok_or() { return booljunc(OK, OR, 0); }
t_ast			*fail_and() { return booljunc(FAIL, AND, 0); }
t_ast			*fail_or() { return booljunc(FAIL, OR, 0); }
t_ast			*ok_and() { return booljunc(OK, AND, 0); }
t_ast			*ok_sep() { return booljunc(OK, SEP, 0); }
t_ast			*fail_sep() { return booljunc(FAIL, SEP, 0); }

t_ast			*notok_or() { return booljunc(OK, OR, 1); }
t_ast			*notfail_and() { return booljunc(FAIL, AND, 1); }
t_ast			*notfail_or() { return booljunc(FAIL, OR, 1); }
t_ast			*notok_and() { return booljunc(OK, AND, 1); }
t_ast			*notok_sep() { return booljunc(OK, SEP, 1); }
t_ast			*notfail_sep() { return booljunc(FAIL, SEP, 1); }

int				check_test_output(char *expected_str)
{
	char	buf[4096];
	int		fd, read_num, res;

	ft_bzero(buf, 4096);
	fd = open(test_output_file, O_RDONLY);
	read_num = read(fd, buf, 4096);
	if (read_num > 0 && read_num < 4096)
		buf[read_num] = '\0';
	else if (read_num == 4096)
		buf[4095] = '\0';
	res = ft_strcmp(expected_str, buf);
	fprintf(stderr, "%s\n", res == 0 ? "list test ok" : "list test failed");
	//fprintf(stderr, "Expected:\t%s\nResult:\t\t%s\n\nMatch? [ %s ]\n\n",
			//expected_str, buf, (res == 0 ? "YES" : "NO"));
	close(fd);
	return (!!res);
}

t_redir	*make_redir(int left, enum e_redirect op, char *right, int is_fd)
{
	t_redir *r;

	r = new_redir();
	r->to_fd = left;
	r->op = op;
	r->from_file = ft_strdup(right);
	r->file_string_represents_fd = is_fd;
	return (r);
}
