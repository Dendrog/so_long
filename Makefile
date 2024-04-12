NAME =          so_long

SRCS =  test.c\

LIB = libft/libft.a\
		ft_printf/libftprintf.a

#HEADR = pipex.h

CC = cc
CFLAGS = -Wall -Wextra -Werror 

OBJS = $(SRCS:.c=.o)

all: $(LIB) $(NAME)

$(LIB):
	@make re -C ./libft
	@make re -C ./ft_printf

$(NAME): $(OBJS)
	$(CC) $(SRCS) $(CFLAGS) -Lmlx -lmlx -lXext -lX11 -lm $(LIB) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	@make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re

