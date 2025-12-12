# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/XX/XX XX:XX:XX by student          #+#    #+#              #
#    Updated: 2024/XX/XX XX:XX:XX by student         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = cube3d

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./minilibx_opengl

# MinilibX
MLX_DIR = ./minilibx_opengl
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Math library
MATH_FLAGS = -lm

# Source files
SRCS_DIR = srcs
PARSING_DIR = $(SRCS_DIR)/parsing

SRCS = $(SRCS_DIR)/main.c \
       $(PARSING_DIR)/parse_config.c \
       $(PARSING_DIR)/parse_map.c \
       $(PARSING_DIR)/parse_utils.c \
       $(PARSING_DIR)/validate_map.c

# Object files
OBJS_DIR = objs
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(MLX) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX):
	@echo "$(YELLOW)Compiling MinilibX...$(NC)"
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(GREEN)MinilibX compiled!$(NC)"

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJS_DIR)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re