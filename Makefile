# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/05 11:09:16 by mdelarbr     #+#   ##    ##    #+#        #
#    Updated: 2019/02/14 12:48:13 by mdelarbr    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = minishell

FLAGS = -g -Wall -Wextra -Werror #-fsanitize=address

SRC =	src/parcing/clean_bis.c \
		src/parcing/clean.c \
		src/parcing/clean_first_split.c \
		src/parcing/count_word.c \
		src/parcing/fill_double.c \
		src/parcing/fill_nothing.c \
		src/parcing/clean_main.c \
		src/exec/builtins.c \
		src/exec/use_execve_bis.c \
		src/exec/builtins_env.c \
		src/exec/builtins_pwd.c \
		src/exec/use_execve.c \
		src/main/lnk_list.c \
		src/main/main.c

OBJ = $(subst .c,.o,$(SRC))

LIGHT_PINK = \033[0;38;5;200m

PINK = \033[0;38;5;198m

DARK_BLUE = \033[0;38;5;110m

GREEN = \033[0;38;5;111m

LIGHT_GREEN = \033[0;38;5;121m

FLASH_GREEN = \033[33;32m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)█"
	@echo "$(DARK_BLUE)\nFichiers de "$(NAME)" compilés."
	@echo "$(DARK_BLUE)libft : "
	@make -C libft/
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -I libft/include -L libft/ -lft
	@echo "$(FLASH_GREEN)Programme "$(NAME)" compilé et prêt à l'usage !\n"

%.o: %.c include/minishell.h
	@gcc $(FLAGS) -I libft/includes -o $@ -c $<
	@echo "$(DARK_BLUE).\c"

clean:
	@rm -rf $(OBJ)
	@make -C libft/ clean
	@echo "$(DARK_BLUE)Suppression des .o de "$(NAME)"\n"

fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
	@echo "$(DARK_BLUE)Suppression de" $(NAME)"\n"

re: fclean all
