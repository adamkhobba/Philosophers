# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adam <adam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 20:08:55 by adam              #+#    #+#              #
#    Updated: 2024/07/15 16:42:10 by adam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc

CFLAGS = #-Wall -Wextra -Werror

SRC = main.c src/parsing.c src/philo_routine.c src/ft_usleep.c\
		utils/ft_atoi.c  src/monitoring.c \

OBJ = ${SRC:.c=.o}

NAME = Philo
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