# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adam <adam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 20:08:55 by adam              #+#    #+#              #
#    Updated: 2024/07/13 12:11:05 by adam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc

CFLAGS = #-Wall -Wextra -Werror

SRC = main.c src/parsing.c src/philo_routine.c\
		utils/ft_atoi.c 

OBJ = ${SRC:.c=.o}

NAME = Philo

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -pthread

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all