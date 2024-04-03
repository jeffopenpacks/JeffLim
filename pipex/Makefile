# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joolim <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/15 16:34:00 by joolim            #+#    #+#              #
#    Updated: 2024/02/06 14:08:23 by joolim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = pipex_utils.c
MANDATORY = pipex.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = pipex
all: ${NAME}

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

OBJS = ${SRCS:.c=.o}
MANDATORYOBJS = ${MANDATORY:.c=.o}

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(NAME): ${MANDATORYOBJS} ${OBJS} $(LIBFT)
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	rm -f ${OBJS} ${MANDATORYOBJS}

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	rm -f ${NAME} ${BONUS}

re: fclean all

.PHONY: all clean fclean re
