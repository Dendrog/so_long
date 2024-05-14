NAME =          so_long

SRCS =  main.c\
		so_long_utils1.c\
		so_long_utils2.c\
		so_long_utils3.c\
		so_long_utils4.c

LIB = libft/libft.a\
		ft_printf/libftprintf.a\
		get_next_line/gnl.a

HEADR = so_long.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

OBJS = $(SRCS:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	@make re -C ./libft
	@make re -C ./ft_printf
	@make re -C ./get_next_line

$(NAME): $(OBJS) $(HEADR)
	$(CC) $(SRCS) $(CFLAGS) -Lmlx -lmlx -lXext -lX11 -lm $(LIB) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	@make clean -C ./libft
	@make clean -C ./ft_printf
	@make clean -C ./get_next_line
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re

