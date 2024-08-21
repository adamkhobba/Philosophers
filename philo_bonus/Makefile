# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 10:23:45 by akhobba           #+#    #+#              #
#    Updated: 2024/08/21 10:47:14 by akhobba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread

SRC = main.c  src/ft_usleep.c src/parsing.c src/monitore.c\
	src/philo_routine.c src/sem.c src/lock_var.c utils/utils.c\
	utils/ft_atoi.c utils/ft_strlen.c \
	utils/utils_parsing.c\

OBJ = ${SRC:.c=.o}

NAME = philo_bonus

INC = -I./include

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -pthread

%.o: %.c
	${CC} ${CFLAGS} $(INC) -c $< -o $@
clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
