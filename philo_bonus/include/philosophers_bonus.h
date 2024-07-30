/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:25:09 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/27 10:26:41 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philosophers_bonus_BONUS_H
# define philosophers_bonus_BONUS_H
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define BLUE "\033[34m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define CYAN "\033[36m"

typedef struct s_philo
{
	pthread_t 		thread;
	size_t			last_meal;
	size_t			current_meal;
	size_t			full;
	size_t			dead;
	int				status;
	int				index_of_philo;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	int				num_times_to_eat;
	size_t			dead_flag;
	int				num_of_philos;
	int				nbr_limits_meals;
	sem_t			*forks;
	sem_t			*sem_print;
	sem_t			*sem_data;
	int				*id;
	t_philo			*philos;
	size_t			start_time;
}					t_data;

// src
int					ft_parsing(char **input, int c);
int					ft_kill(int *id, t_data *data);
void				ft_free(t_data *data);
void				ft_philos_routine(t_philo *data);
size_t get(t_data *data, size_t *var);
void set(t_data *data, size_t *var, size_t value);
int					ft_usleep(size_t milliseconds);
int					ft_kill_all(int *id);
size_t				get_current_time(void);
void				*ft_monitoring(void *args);
// void				ft_set_dead(t_data *data, int value);

// utils
long				ft_atoi(const char *nptr);
int					ft_strlen(char *str);
int					ft_args_nbr(int c);
int					ft_isdigit(int c);
#endif