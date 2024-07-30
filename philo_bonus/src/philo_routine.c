/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:17 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/30 20:11:05by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void    ft_eat(t_philo *philo)
{
	// if (!philo->data->dead_flag)
	if (!get(philo->data, &philo->data->dead_flag))
		return ;
    sem_wait(philo->data->forks);
	sem_wait(philo->data->sem_print);
	printf("%s %zu %d has taken a fork\n%s", BLUE, get_current_time()
			- philo->data->start_time, philo->index_of_philo, NC);
	sem_post(philo->data->sem_print);
    sem_wait(philo->data->forks);
	// if (!philo->data->dead_flag)
	if (!get(philo->data, &philo->data->dead_flag))
		return ;
	sem_wait(philo->data->sem_print);
	printf("%s %zu %d has taken a fork\n%s", BLUE, get_current_time()
			- philo->data->start_time, philo->index_of_philo, NC);
	printf("%s %zu %d is eating\n%s", CYAN, get_current_time()
			- philo->data->start_time, philo->index_of_philo, NC);
	sem_post(philo->data->sem_print);
    // philo->last_meal = get_current_time();
	set(philo->data, &philo->last_meal, get_current_time());
	ft_usleep(philo->data->time_to_eat);
    sem_post(philo->data->forks);
    sem_post(philo->data->forks);
}

void    ft_philos_routine(t_philo *philo)
{
	int	status;

	status = -1;
    // philo->last_meal = get_current_time();
	set(philo->data, &philo->last_meal, get_current_time());
	// printf("last_meal = %zu\n", philo->last_meal);
	// while (philo->data->dead_flag)
	while (get(philo->data, &philo->data->dead_flag))
	{
		ft_eat(philo);
		if (!get(philo->data, &philo->data->dead_flag))
			break ;
		sem_wait(philo->data->sem_print);
			printf("%s %zu %d is sleeping\n%s", YELLOW, get_current_time()
				- philo->data->start_time, philo->index_of_philo, NC);
		sem_post(philo->data->sem_print);
		ft_usleep(philo->data->time_to_sleep); 
		// if (!philo->data->dead_flag)
		if (!get(philo->data, &philo->data->dead_flag))
			break ;
		sem_wait(philo->data->sem_print);
			printf("%s %zu %d is thinking%s\n", GREEN, (get_current_time()
				- philo->data->start_time), philo->index_of_philo, NC);
		sem_post(philo->data->sem_print);
	}
	pthread_join(philo->thread, NULL);
	status = philo->status;
	ft_free(philo->data);
	exit(status);
}
