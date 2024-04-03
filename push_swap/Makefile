SRCS = free_all.c make_list.c push.c reverse.c rotate.c solve4.c swap.c sort_three.c special_move.c check_error.c lst_functions.c elegant_push.c
BONUSSRCS = checker.c
MANDATORY = main.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = push_swap
BONUS = checker
all: ${NAME} ${BONUS}
bonus: ${BONUS}

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

OBJS = ${SRCS:.c=.o}
MANDATORYOBJS = ${MANDATORY:.c=.o}
BONUSOBJS = $(BONUSSRCS:.c=.o)

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(NAME): ${MANDATORYOBJS} ${OBJS} $(LIBFT)
	${CC} ${CFLAGS} -o $@ $^

$(BONUS): $(BONUSOBJS) $(OBJS) $(LIBFT)
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean
	rm -f ${OBJS} ${MANDATORYOBJS} ${BONUSOBJS}

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	rm -f ${NAME} ${BONUS}

re: fclean all

.PHONY: all clean fclean re
