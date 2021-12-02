NAME = pipex
NAME_BONUS = pipex_bonus
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

SRC = pipex.c
SRC_BONUS = pipex_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Wall -Werror -Wextra -O2

all: $(LIBFT) $(PRINTF) $(NAME) pipex.h

bonus: $(LIBFT) $(PRINTF) $(NAME_BONUS) pipex.h

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C printf

$(NAME): $(OBJ) Makefile pipex.h $(LIBFT) $(PRINTF)
	gcc $(OBJ) -L./libft -lft -L./printf -lftprintf -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS) Makefile pipex.h $(LIBFT)
	gcc $(OBJ_BONUS) -L./libft -lft -L./printf -lftprintf -o $(NAME_BONUS)

%.o:	%.c
	gcc $(FLAGS) -I libft -I printf -c $< -o $@

clean:
	make clean -sC libft
	make clean -sC printf
	rm -f $(OBJ) $(OBJ_BONUS)

fclean:	clean
	make fclean -sC libft
	make fclean -sC printf
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean all re