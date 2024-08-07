/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:26:03 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/07 15:44:03 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print_msg(t_philo *data, char *status, char *color)
{
	pthread_mutex_lock(&data->data->lock_print);
	if (!get(&data->data->dead_lock, &data->data->dead_flag))
	{
		pthread_mutex_unlock(&data->data->lock_print);
		return ;
	}
	printf("%s %zu %d %s\n%s", color, get_current_time() - data->start_time,
		data->index_of_philo, status, NC);
	pthread_mutex_unlock(&data->data->lock_print);
}

void	ft_eat(t_philo *data)
{
	pthread_mutex_lock(data->forks);
	if (get(&data->data->dead_lock, &data->data->dead_flag))
		ft_print_msg(data, "has taken a fork", BLUE);
	if (data->data->num_of_philos == 1)
	{
		pthread_mutex_unlock(data->forks_l);
		return ;
	}
	pthread_mutex_lock(data->forks_l);
	if (get(&data->data->dead_lock, &data->data->dead_flag))
		ft_print_msg(data, "has taken a fork", BLUE);
	if (get(&data->data->dead_lock, &data->data->dead_flag))
		ft_print_msg(data, "is eating", CYAN);
	set(&data->locker, &data->full, data->full + 1);
	set(&data->locker, &data->last_meal, get_current_time());
	ft_usleep(data->data->time_to_eat);
	pthread_mutex_unlock(data->forks_l);
	pthread_mutex_unlock(data->forks);
}

void	*ft_philos_routine(void *args)
{
	t_philo	*data;

	data = (t_philo *)args;
	ft_set_dead(data->data, 1);
	if (data->index_of_philo % 2 == 0)
		ft_usleep(60);
	set(&data->locker, &data->last_meal, get_current_time());
	while (get(&data->data->dead_lock, &data->data->dead_flag))
	{
		ft_eat(data);
		if (!get(&data->data->dead_lock, &data->data->dead_flag)
			|| data->data->num_of_philos == 1)
			break ;
		ft_print_msg(data, "is sleeping", YELLOW);
		ft_usleep(data->data->time_to_sleep);
		if (!get(&data->locker, &data->dead))
			break ;
		ft_print_msg(data, "is thinking", GREEN);
		usleep(500);
	}
	return (NULL);
}
