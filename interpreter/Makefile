files := $(wildcard *.c) $(wildcard ../src/*.c)
files := $(filter-out ../src/main.c, $(files))
interpreter: $(files)
	gcc -Wall -Wextra -g -I../includes -I../libft/includes -L../libft -lft -ltermcap -o $@ $(files)
