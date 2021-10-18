NAME = pipex
LIBFT = libft.a

SRC = pipex.c

HEADER = pipex.h
OBJ_SRC = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra
INC_PATH = libft

all: $(LIBFT) $(NAME) 

$(LIBFT):
	@make -C libft

$(NAME): $(OBJ_SRC) $(HEADER) Makefile $(LIBFT)
	gcc $(OBJ_SRC) -L $(INC_PATH) -l (LIBFT) -o $(NAME)

%.o:	%.c
	@gcc $(FLAGS) -I $(INC_PATH) -c $< -o $@

clean:
	@make clean -C $(INC_PATH)
	@rm $(OBJ_SRC)

fclean:	clean
	@make fclean -C $(INC_PATH)
	@rm $(NAME)

re: fclean all

.PHONY: clean fclean all re