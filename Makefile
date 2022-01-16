NAME = pipex
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

SRC = pipex.c close_free.c launch_cmd.c get_path.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -O2

all: $(NAME)

$(NAME): $(OBJ) Makefile pipex.h $(LIBFT) $(PRINTF)
	gcc $(OBJ) -L./libft -lft -L./printf -lftprintf -o $(NAME)

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C printf

%.o:	%.c
	gcc $(FLAGS) -I libft -I printf -c $< -o $@

clean:
	make clean -sC libft
	make clean -sC printf
	rm -f $(OBJ)

fclean:	clean
	make fclean -sC libft
	make fclean -sC printf
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re