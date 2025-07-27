# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/21 20:20:24 by jomunoz           #+#    #+#              #
#    Updated: 2025/07/27 20:10:32 by jomunoz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = fdf.c assigments.c helper.c project_isometric.c parsing.c get_next_line.c \
	get_colour.c project_orthographic.c rotation.c
OBJ = $(SRC:.c=.o)

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz


all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c fdf.h
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re