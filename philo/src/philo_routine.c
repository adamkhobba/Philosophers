/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:26:03 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/22 21:26:05 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat_v2(t_philo *data)
{
	pthread_mutex_lock(&data->forks);
	pthread_mutex_lock(data->forks_l);
	set(&data->locker, &data->last_meal, get_current_time());
	if (get(&data->locker, &data->dead))
		printf("%s %zu %d has taken a fork\n%s", BLUE, get_current_time()
			- data->start_time, data->index_of_philo, NC);
	if (get(&data->locker, &data->dead))
		printf("%s %zu %d is eating\n%s", CYAN, get_current_time()
			- data->start_time, data->index_of_philo, NC);
	set(&data->locker, &data->full, data->full + 1);
	ft_usleep(data->data->time_to_eat);
	pthread_mutex_unlock(data->forks_l);
	pthread_mutex_unlock(&data->forks);
}

void	ft_eat(t_philo *data)
{
	pthread_mutex_lock(data->forks_l);
	pthread_mutex_lock(&data->forks);
	set(&data->locker, &data->last_meal, get_current_time());
	if (get(&data->locker, &data->dead))
		printf("%s %zu %d has taken a fork\n%s", BLUE, get_current_time()
			- data->start_time, data->index_of_philo, NC);
	if (get(&data->locker, &data->dead))
		printf("%s %zu %d is eating\n%s", CYAN, get_current_time()
			- data->start_time, data->index_of_philo, NC);
	set(&data->locker, &data->full, data->full + 1);
	ft_usleep(data->data->time_to_eat);
	pthread_mutex_unlock(&data->forks);
	pthread_mutex_unlock(data->forks_l);
}

void	*ft_philos_routine(void *args)
{
	t_philo	*data;

	data = (t_philo *)args;
	ft_set_dead(data->data, 1);
	if (data->index_of_philo % 2 == 0)
		ft_usleep(60);
	set(&data->locker, &data->last_meal, get_current_time());
	while (get(&data->locker, &data->data->dead_flag))
	{
		if (data->index_of_philo % 2 == 0)
			ft_eat(data);
		else
			ft_eat_v2(data);
		if (get(&data->locker, &data->dead))
		{
			printf("%s %zu %d is sleeping\n%s", YELLOW, get_current_time()
				- data->start_time, data->index_of_philo, NC);
			ft_usleep(data->data->time_to_sleep);
		}
		if (get(&data->locker, &data->dead))
			printf("%s %zu %d is thinking%s\n", GREEN, (get_current_time()
					- data->start_time), data->index_of_philo, NC);
	}
	return (NULL);
}
