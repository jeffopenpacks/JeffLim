# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joolim <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 15:53:58 by joolim            #+#    #+#              #
#    Updated: 2024/01/08 11:24:44 by joolim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memcpy.c ft_memchr.c ft_memcmp.c ft_memmove.c \
ft_memset.c ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_putendl_fd.c \
ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
ft_substr.c ft_tolower.c ft_toupper.c

SOURCES += specc.c specd.c specmod.c specp.c specs.c specu.c specx.c printit.c ft_printf.c

SOURCES += get_next_line.c get_next_line_utils.c

BONUSSRC = ft_lstadd_back.c ft_lstadd_front.c ft_lstsize.c ft_lstmap.c ft_lstnew.c \
	   ft_lstclear.c ft_lstiter.c ft_lstdelone.c ft_lstlast.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE
NAME = libft.a
all: ${NAME}

OBJECTS = ${SOURCES:.c=.o}
BONUSOBJ = ${BONUSSRC:.c=.o}

$(NAME): ${OBJECTS} ${BONUSOBJ}
	ar rcs $@ $^

bonus: ${OBJECTS} ${BONUSOBJ}
	ar rcs ${NAME} $^

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f ${OBJECTS} ${BONUSOBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
