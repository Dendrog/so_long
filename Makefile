NAME =          so_long

SRCS =  test.c\

LIB = libft/libft.a\
		ft_printf/libftprintf.a\
		get_next_line/gnl.a

#HEADR = 

CC = cc
CFLAGS = -Wall -Wextra -Werror 

OBJS = $(SRCS:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	@make re -C ./libft
	@make re -C ./ft_printf
	@make re -C ./get_next_line

$(NAME): $(OBJS)
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

