NAME = pipex
NAME_BONUS = pipex_bonus

SRC = pipex.c
SRC_BONUS = pipex_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Wall -Werror -Wextra

all: $(NAME) 

bonus: $(NAME_BONUS)

$(NAME): $(OBJ) Makefile
	gcc $(OBJ) -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS) Makefile
	gcc $(OBJ_BONUS) -o $(NAME_BONUS)

%.o:	%.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean:	clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean all re