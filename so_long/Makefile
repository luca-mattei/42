NAME = so_long

CC = cc
UNAME_S := $(shell uname -s)

SRCDIR = src
OBJDIR = obj
LIBDIR = lib
INCDIR = inc

ifeq ($(UNAME_S),Linux)
	MLX_DIR = minilibx-linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lz
	MLX_INC = -I$(MLX_DIR)
	CFLAGS = -Wall -Werror -Wextra -g3 -O3
else
	MLX_DIR = minilibx_opengl
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	MLX_INC = -I$(MLX_DIR)
	CFLAGS = -Wall -Werror -Wextra -g3
endif

FILES = check_and_init_map.c \
	map_elements_verification.c \
	map_check_playable.c \
	free.c \
	main.c \
	init_game.c \
	handle_key.c

SRC = $(addprefix $(SRCDIR)/, $(FILES))
OBJ = $(addprefix $(OBJDIR)/, $(FILES:.c=.o))

HEADERS = $(INCDIR)/so_long.h 
INCLUDES = $(MLX_INC) -I$(LIBDIR)/libft -I$(LIBDIR)/ft_printf -I$(INCDIR)

LIBFT = $(LIBDIR)/libft/libft.a
FT_PRINTF = $(LIBDIR)/ft_printf/libftprintf.a
MLX = $(MLX_DIR)/libmlx.a

SUCCESS = "\033[1;35mSuccessful compilation on $(UNAME_S)!\033[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(MLX)
	@$(CC) $(OBJ) $(LIBFT) $(FT_PRINTF) $(MLX_FLAGS) -o $(NAME)
	@echo $(SUCCESS)

$(LIBFT):
	@make -C $(LIBDIR)/libft

$(FT_PRINTF):
	@make -C $(LIBDIR)/ft_printf

$(MLX):
	@make -C $(MLX_DIR)

clean:
	@$(RM) -r $(OBJDIR)
	@make -C $(LIBDIR)/libft clean
	@make -C $(LIBDIR)/ft_printf clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBDIR)/libft fclean
	@make -C $(LIBDIR)/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
