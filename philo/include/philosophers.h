/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:04:39 by adam              #+#    #+#             */
/*   Updated: 2024/08/07 12:06:40 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <limits.h>
# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define BLUE "\033[34m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define CYAN "\033[36m"

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	forks;
	pthread_mutex_t	*forks_l;
	pthread_mutex_t	locker;
	size_t			last_meal;
	size_t			current_meal;
	size_t			start_time;
	size_t			full;
	size_t			dead;
	int				index_of_philo;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	int				num_times_to_eat;
	pthread_mutex_t	lock_print;
	size_t			dead_flag;
	int				num_of_philos;
	int				nbr_limits_meals;
	int				start;
	int				end;
	t_philo			*philos;
}					t_data;

// src
int					ft_parsing(char **input, int c);
void				ft_free_data(t_data *data);
int					ft_free_mutex(t_data *data, int lim);
void				*ft_philos_routine(void *args);
int					ft_usleep(size_t milliseconds);
size_t				get_current_time(void);
int					ft_monitoring(void *data);
void				ft_set_dead(t_data *data, int value);
void				set(pthread_mutex_t *locker, size_t *var, size_t value);
size_t				get(pthread_mutex_t *locker, size_t *var);

// utils
int					ft_checknum(char **str);
int					ft_num_agrs(char *str);
long				ft_atoi(const char *nptr);
int					ft_strlen(char *str);
int					ft_args_nbr(int c);
int					ft_isdigit(int c);
#endif