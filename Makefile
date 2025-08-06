# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/21 20:20:24 by jomunoz           #+#    #+#              #
#    Updated: 2025/08/05 19:41:29 by jomunoz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Iinclude -Wall -Wextra -Werror -Iinclude
MLX_DIR = minilibx-linux

OBJDIR = obj

MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC = fdf.c \
      projections/project_isometric.c \
      projections/project_orthographic.c \
      parsing/parsing.c \
      parsing/get_next_line.c \
      assignments/assignments.c \
      key_handlers/key_handler.c \
      key_handlers/key_handler2.c \
      projections/drawing.c \
      projections/rotations.c \
      frees/frees.c \
      frees/frees2.c \
      utils/utils.c \
      utils/utils2.c

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -rf $(OBJDIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
