NAME = libftprintf.a

SRCS = src/ft_char.c\
	  src/ft_str.c\
	  src/ft_printf.c\
	  src/ft_decimal.c\
	  src/ft_hexa.c\
	  src/ft_pointer.c\
	  src/ft_unsigned_decimal.c

OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar rcs $(NAME) $(OBJS)
	ar x $(LIBFT)
	ar rcs $(NAME) *.o
	$(RM) *.o

$(LIBFT):
	make bonus -C $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

