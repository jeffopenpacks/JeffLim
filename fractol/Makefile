# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joolim <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 18:13:01 by joolim            #+#    #+#              #
#    Updated: 2024/02/17 12:58:58 by joolim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fractol.c fractol_utils.c render.c hooks.c
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
MAIN = srcs/fractol.c

SRC_DIR = srcs/
OBJ_DIR = objs/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = fractol
all: ${NAME}

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

MLX_PATH = ./minilibx
MLX = $(MLX_PATH)/libmlx.a

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(MLX):
	@make -C $(MLX_PATH)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): ${OBJS} $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean
	rm -rf ${OBJ_DIR}

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@make -C $(MLX_PATH) clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re

