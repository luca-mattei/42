NAMEC = client.a
NAMES = server.a

SRCS = server.c

SRCC = client.c

OBJS = ${SRCS:.c=.o} 
OBJC = ${SRCC:.c=.o} 

CC = cc

CFLAGS = -Wall -Werror -Wextra

all : $(NAMEC) $(NAMES)

$(NAMES): $(OBJS)
	make -C printf
	cp printf/libftprintf.a .
	mv libftprintf.a ${NAMES}
	ar rcs $(NAMES) $(OBJS)

$(NAMEC): $(OBJC)
	ar rcs $(NAMEC) $(OBJC)

clean:
	make clean -C ./printf
	rm -rf $(OBJS) $(OBJC)

fclean: clean
	make fclean -C ./printf
	rm -rf $(NAMES) $(NAMEC)

re: fclean all



