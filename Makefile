# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 14:40:06 by tjourdan          #+#    #+#              #
#    Updated: 2025/10/27 15:44:30 by tjourdan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude -I$(MLX_PATH) -g3

MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

LIBFT_DIR	= lib
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_DIR		= src
OBJ_DIR		= obj
INCLUDES	= include/cub3d.h $(LIBFT_DIR)/libft.h $(MLX_PATH)mlx.h

SRCS		=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/check.c \
				$(SRC_DIR)/init.c \
				$(SRC_DIR)/initimg.c \
				$(SRC_DIR)/key.c \
				$(SRC_DIR)/lines.c \
				$(SRC_DIR)/maps.c \
				$(SRC_DIR)/move.c \
				$(SRC_DIR)/parsing.c \
				$(SRC_DIR)/raycasting.c \
				$(SRC_DIR)/render.c \
				$(SRC_DIR)/free.c \
				$(SRC_DIR)/dda.c \
				$(SRC_DIR)/draw.c \
				$(SRC_DIR)/texture.c \
				$(SRC_DIR)/calculate.c \
				$(SRC_DIR)/rgb.c \
				$(SRC_DIR)/player.c \
				$(SRC_DIR)/check_pos.c \
				$(SRC_DIR)/utils.c

OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Compilation rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build executable
$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lXext -lX11 -lm -lz -o $(NAME)

# Build MLX library
$(MLX):
	$(MAKE) -C $(MLX_PATH)

# Build libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Standard rules
all: $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	-$(MAKE) clean -C $(MLX_PATH)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	-$(MAKE) clean -C $(MLX_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
