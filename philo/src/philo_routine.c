/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:26:03 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/17 11:36:00 by akhobba          ###   ########.fr       */
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
		pthread_mutex_unlock(data->forks);
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
	t_philo	*philo;

	philo = (t_philo *)args;
	ft_set_dead(philo->data, 1);
	if (philo->index_of_philo % 2 == 0)
		ft_usleep(60);
	set(&philo->locker, &philo->last_meal, get_current_time());
	while (get(&philo->data->dead_lock, &philo->data->dead_flag))
	{
		ft_eat(philo);
		if (!get(&philo->data->dead_lock, &philo->data->dead_flag)
			|| philo->data->num_of_philos == 1)
			break ;
		ft_print_msg(philo, "is sleeping", YELLOW);
		ft_usleep(philo->data->time_to_sleep);
		if (!get(&philo->locker, &philo->dead))
			break ;
		ft_print_msg(philo, "is thinking", GREEN);
		if (philo->data->num_of_philos > 100)
		usleep(50 * philo->data->num_of_philos);
		else
		usleep(200 * philo->data->num_of_philos);
	}
	return (NULL);
}
