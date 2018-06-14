#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*string = NULL;
	char	*out_file = NULL;
	int		rval = 0;
	int		sleep_amt = 0;
	int		i;

	for (i = 0; i < argc - 2; i++)
	{
		if (strstr(argv[i], "--out="))
			out_file = strchr(argv[i], '=') + 1;
		else if (strstr(argv[i], "--sleep="))
			sleep_amt = atoi(strchr(argv[i], '=') + 1);
		else if (strstr(argv[i], "--"))
			fprintf(stderr, "write_and exit: Unknown option: %s\n", argv[i]);
	}
	FILE *f = out_file ? fopen(out_file, "a+") : stderr;
	string = argv[i++];
	rval = atoi(argv[i]);
	fprintf(f, "%s", string);
	fclose(f);
	sleep(sleep_amt);
	return (rval);
}
