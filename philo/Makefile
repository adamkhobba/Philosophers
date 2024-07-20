# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adam <adam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 20:08:55 by adam              #+#    #+#              #
#    Updated: 2024/07/20 20:31:28 by adam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c src/parsing.c src/monitoring.c src/philo_routine.c\
		src/ft_usleep.c src/free.c\
		utils/ft_atoi.c utils/ft_strlen.c\

OBJ = ${SRC:.c=.o}

NAME = Philo
INC = -I./include
all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -pthread  -fsanitize=thread -g

%.o: %.c
	${CC} ${CFLAGS} $(INC) -c $< -o $@
clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all