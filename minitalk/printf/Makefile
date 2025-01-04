NAME = libftprintf.a

SRCS = src/ft_char.c	src/ft_str.c	src/ft_printf.c\
	   src/ft_decimal.c	src/ft_hexa.c	src/ft_pointer.c\
	   src/ft_unsigned_decimal.c

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C libft
	cp libft/libft.a .
	mv libft.a ${NAME}
	ar rcs $(NAME) $(OBJS)

clean:
	make clean -C ./libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all

