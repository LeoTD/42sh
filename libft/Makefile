# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 19:18:37 by ltanenba          #+#    #+#              #
#    Updated: 2018/06/15 23:52:45 by ltanenba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I includes
INCLUDES	= includes/libft.h \
			  includes/ft_printf.h \
			  includes/ft_prompt.h

LIBC_SRC	= ft_memset.c \
			  ft_bzero.c \
			  ft_memcpy.c \
			  ft_memccpy.c \
			  ft_memmove.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_strlen.c \
			  ft_strdup.c \
			  ft_strndup.c \
			  ft_strcpy.c \
			  ft_strncpy.c \
			  ft_strcat.c \
			  ft_strncat.c \
			  ft_strlcat.c \
			  ft_strchr.c \
			  ft_strrchr.c \
			  ft_strstr.c \
			  ft_strnstr.c \
			  ft_strcmp.c \
			  ft_strncmp.c \
			  ft_atoi.c \
			  ft_isalpha.c \
			  ft_isdigit.c \
			  ft_isascii.c \
			  ft_isalnum.c \
			  ft_isprint.c \
			  ft_toupper.c \
			  ft_tolower.c \

ADD_SRC		= ft_putchar.c \
			  ft_putchar_fd.c \
			  ft_putstr.c \
			  ft_putstr_fd.c \
			  ft_putnbr.c \
			  ft_putnbr_fd.c \
			  ft_putendl.c \
			  ft_putendl_fd.c \
			  ft_itoa.c \
			  ft_memalloc.c \
			  ft_memdel.c \
			  ft_strnew.c \
			  ft_strdel.c \
			  ft_strclr.c \
			  ft_striter.c \
			  ft_striteri.c \
			  ft_strmap.c \
			  ft_strmapi.c \
			  ft_strequ.c \
			  ft_strnequ.c \
			  ft_strsub.c \
			  ft_strjoin.c \
			  ft_strjoin_free.c \
			  ft_strtrim.c \
			  ft_strsplit.c

EX_SRC		= ft_itoa_base.c \
			  ft_strrev.c \
			  ft_isspace.c \
			  ft_strjoin_null.c \
			  ft_isupper.c \
			  ft_islower.c \
			  ft_lstsort.c

BONUS_SRC	= ft_lstnew.c \
			  ft_lstdelone.c \
			  ft_lstdel.c \
			  ft_lstadd.c \
			  ft_lstiter.c \
			  ft_lstmap.c \
			  ft_numlen_base.c \
			  ft_copyuntil.c \
			  get_next_line.c

CLIST_SRC	= clist_delink.c \
			  clist_relink.c \
			  clist_lstcadd.c \
			  ft_lstcnew.c

PRINTF_SRC	= tools.c \
			  ft_printf.c \
			  convert.c \
			  flags.c \
			  numberconv.c \
			  helper.c \
			  buffer.c

PROMPT_SRC	= cursor_movement.c \
			  delete.c \
			  edit_loop.c \
			  ft_prompt.c \
			  history.c \
			  multi_print.c \
			  print.c \
			  setup.c

PF_SRC		= $(addprefix ft_printf/, $(PRINTF_SRC))
PRT_SRC		= $(addprefix ft_prompt/, $(PROMPT_SRC))

FILES		+= $(LIBC_SRC) $(ADD_SRC) $(EX_SRC) $(BONUS_SRC) $(CLIST_SRC) $(PF_SRC) $(PRT_SRC)

SRC			= $(addprefix src/, $(FILES))
OBJ			= $(addprefix obj/, $(FILES:.c=.o))

# Cosmetics Section:

OK_COLOR	= \033[38;5;105;1m
OBJ_COLOR	= \033[38;5;208m
COM_COLOR	= \033[38;5;200m
LIB_COLOR	= \033[1;32m
NO_COLOR    = \033[m

COM_STRING	= "Compiling:"

# End Cosmetics.

all: $(NAME)

$(NAME): $(OBJ)
	@printf "%b" "$(LIB_COLOR)Creating Archive: $(OK_COLOR)$@\n$(NO_COLOR)"
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -rf obj/

fclean: clean
	@printf "Cleaning up libft...\n"
	@rm -f $(NAME)

obj:
	@printf "Creating obj/ directory...\n"
	@mkdir obj/
	@mkdir obj/ft_printf
	@mkdir obj/ft_prompt

obj/%.o: src/%.c | obj
	@printf "%b" "$(COM_COLOR)  $(COM_STRING) $(OBJ_COLOR)$@\n$(NO_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

norm:
	@printf "%b" "$(LIB_COLOR)Checking Norm...\n$(NO_COLOR)"
	@norminette $(SRC) $(INCLUDES)

objfiles: $(OBJ)
	@printf "%b" "$(LIB_COLOR)Libft: Created *.o files...\n$(NO_COLOR)"

re: fclean all

.PHONY: clean fclean all re
