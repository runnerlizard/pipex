NAME	= libftprintf.a

SRCS	= ft_printf.c ft_putchar.c ft_putnbr_fd.c 

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Werror -Wextra

.c.o:
		cc $(CFLAGS) -c $< -o $(<:.c=.o)
	
all:	$(NAME)
		
$(NAME):  ${OBJS} ft_printf.h
		ar rcs $(NAME) $(OBJS)


clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
