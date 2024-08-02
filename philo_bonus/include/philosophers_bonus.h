/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:49:58 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/01 17:00:36 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

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
	int				status;
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
void				ft_philos_routine(t_philo *philo, t_data *data);
size_t				get(t_data *data, size_t *var);
void				set(t_data *data, size_t *var, size_t value);
int					ft_usleep(size_t milliseconds);
int					ft_kill_all(int *id);
size_t				get_current_time(void);
void				*ft_monitoring(void *args);
// void				ft_set_dead(t_data *data, int value);

// utils
int					ft_init_sem(t_data data, sem_t **sem_print, sem_t **forks);
void				ft_wait(int *id, t_data *pdata);
int					ft_init_pointers(t_philo *philo, int *id, t_data *data);
long				ft_atoi(const char *nptr);
void				ft_unlink(void);
int					ft_strlen(char *str);
int					ft_args_nbr(int c);
int					ft_isdigit(int c);
#endif