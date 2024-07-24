# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joolim <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 13:58:58 by joolim            #+#    #+#              #
#    Updated: 2024/07/13 14:09:06 by joolim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = init.c signal.c utils.c lexer.c lexer2.c process.c parse.c parse2.c handle_redir.c dolla.c ft_echo_cd.c ft_cd.c ft_env.c ft_exit.c ft_export.c ft_export2.c ft_pwd.c ft_unset.c execute.c execute_signals.c path_functions.c path_functions2.c pipe.c pipe2.c redirection.c heredoc.c heredoc2.c built_ins.c clean_exit.c safe_fn.c
MANDATORY = main.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDLIBS = -lreadline -lhistory
NAME = minishell
all: ${NAME}

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

OBJS = ${SRCS:.c=.o}
MANDATORYOBJS = ${MANDATORY:.c=.o}

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(NAME): ${MANDATORYOBJS} ${OBJS} $(LIBFT)
	${CC} ${CFLAGS} -o $@ $^ $(LDLIBS)

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	rm -f ${OBJS} ${MANDATORYOBJS}

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
