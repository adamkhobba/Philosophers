# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 20:08:55 by adam              #+#    #+#              #
#    Updated: 2024/07/23 17:20:27 by akhobba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3 

SRC = main.c src/parsing.c src/monitoring.c src/philo_routine.c\
		src/ft_usleep.c src/free.c src/ft_lockvar.c\
		utils/ft_atoi.c utils/ft_strlen.c utils/utils_monitor.c utils/utils_parsing.c\

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