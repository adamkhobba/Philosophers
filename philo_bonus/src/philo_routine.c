/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:52:00 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/17 19:52:23 by akhobba          ###   ########.fr       */
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
	if (philo->data->num_of_philos == 1)
		return ;
	sem_wait(philo->data->forks);
	set(philo->data, &philo->full, philo->full + 1);
	if (!get(philo->data, &philo->data->dead_flag))
		return ;
	sem_wait(philo->data->sem_print);
	printf("%s %zu %d has taken a fork\n%s", BLUE, get_current_time()
		- philo->data->start_time, philo->index_of_philo, NC);
	sem_post(philo->data->sem_print);
	sem_wait(philo->data->sem_print);
	printf("%s %zu %d is eating\n%s", CYAN, get_current_time()
		- philo->data->start_time, philo->index_of_philo, NC);
	sem_post(philo->data->sem_print);
	set(philo->data, &philo->last_meal, get_current_time());
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	ft_usleep_right(t_data *data)
{
	if (data->num_of_philos > 100)
		usleep(10 * data->num_of_philos);
	else
		usleep(200 * data->num_of_philos);
}

void	ft_philos_routine(t_philo *philo, t_data *data)
{
	set(philo->data, &philo->last_meal, get_current_time());
	while (get(philo->data, &philo->data->dead_flag))
	{
		ft_eat(philo);
		if (philo->data->num_of_philos == 1
			|| !get(philo->data, &philo->data->dead_flag))
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
		ft_usleep_right(data);
	}
	pthread_join(philo->thread, NULL);
	set(philo->data, &data->status, philo->status);
	sem_post(data->eatten);
	ft_free(philo->data);
	exit(data->status);
}
