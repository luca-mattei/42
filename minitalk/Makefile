NAMEC = client.a
NAMES = server.a

SRCS = server.c

SRCC = client.c

OBJS = ${SRCS:.c=.o} 
OBJC = ${SRCC:.c=.o} 
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
PRINTF_PATH = printf
PRINTF = $(PRINTF_PATH)/libftprintf.a

all : $(NAMEC) $(NAMES)

$(NAMES): $(OBJS) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) -o $(NAMES)

$(NAMEC): $(OBJC)  $(PRINTF)
	$(CC) $(CFLAGS) $(OBJC) $(PRINTF) -o $(NAMEC)

$(PRINTF):
	make -C $(PRINTF_PATH)

clean:
	make clean -C $(PRINTF_PATH)
	$(RM) $(OBJS) $(OBJC)

fclean: clean
	make fclean -C $(PRINTF_PATH)
	$(RM) $(NAMES) $(NAMEC)

re: fclean all

.PHONY: all clean fclean re

