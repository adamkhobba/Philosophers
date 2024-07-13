/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:04:39 by adam              #+#    #+#             */
/*   Updated: 2024/07/13 16:09:39 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stddef.h>
#include <sys/time.h>

#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t *forks;
}					t_philo;

typedef struct s_data
{
	int				dead_flag;
	size_t			time_to_die;
	int 			num_times_to_eat;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_of_philos;
	t_philo			*philos;
}					t_data;

int ft_parsing(char **input, int c);
long	ft_atoi(const char *nptr);
void *ft_philos_routine(void *args);

#endif