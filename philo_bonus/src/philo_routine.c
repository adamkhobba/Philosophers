/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:52:00 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/03 19:52:18 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_eat(t_philo *philo)
{
	if (!get(philo->data, &philo->data->dead_flag))
		return ;
	sem_wait(philo->data->forks);
	sem_wait(philo->data->sem_print);
	printf("%s %zu %d has taken a fork\n%s", BLUE, get_current_time()
		- philo->data->start_time, philo->index_of_philo, NC);
	sem_post(philo->data->sem_print);
	sem_wait(philo->data->forks);
	set(philo->data, &philo->full, philo->full + 1);
	if (!get(philo->data, &philo->data->dead_flag)
		|| philo->data->num_of_philos == 1)
		return ;
	sem_wait(philo->data->sem_print);
	printf("%s %zu %d has taken a fork\n%s", BLUE, get_current_time()
		- philo->data->start_time, philo->index_of_philo, NC);
	printf("%s %zu %d is eating\n%s", CYAN, get_current_time()
		- philo->data->start_time, philo->index_of_philo, NC);
	sem_post(philo->data->sem_print);
	set(philo->data, &philo->last_meal, get_current_time());
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	ft_philos_routine(t_philo *philo, t_data *data)
{
	set(philo->data, &philo->last_meal, get_current_time());
	while (get(philo->data, &philo->data->dead_flag))
	{
		ft_eat(philo);
		if (!get(philo->data, &philo->data->dead_flag)
			|| philo->data->num_of_philos == 1)
			break ;
		sem_wait(philo->data->sem_print);
		printf("%s %zu %d is sleeping\n%s", YELLOW, get_current_time()
			- philo->data->start_time, philo->index_of_philo, NC);
		sem_post(philo->data->sem_print);
		ft_usleep(philo->data->time_to_sleep);
		if (!get(philo->data, &philo->data->dead_flag))
			break ;
		sem_wait(philo->data->sem_print);
		printf("%s %zu %d is thinking%s\n", GREEN, (get_current_time()
				- philo->data->start_time), philo->index_of_philo, NC);
		sem_post(philo->data->sem_print);
		usleep(500);
	}
	pthread_join(philo->thread, NULL);
	data->status = philo->status;
	ft_free(philo->data);
	exit(data->status);
}
