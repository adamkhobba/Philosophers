/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:17 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/29 13:04:32 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void    ft_eat(t_philo *data)
{
    sem_wait(data->data->sem);
    sem_wait(data->data->sem);
    data->last_meal = get_current_time();
	printf("%s %zu %d has taken a fork\n%s", BLUE, get_current_time()
			- data->start_time, data->index_of_philo, NC);
	printf("%s %zu %d is eating\n%s", CYAN, get_current_time()
			- data->start_time, data->index_of_philo, NC);
			ft_usleep(data->data->time_to_eat); 
    sem_post(data->data->sem);
    sem_post(data->data->sem);
}

void    ft_philos_routine(t_philo *data)
{
	// ft_set_dead(data->data, 1);
    data->last_meal = get_current_time();
	while (data->data->dead_flag)
	{
            // eat
			ft_eat(data);
            printf("%s %zu %d is sleeping\n%s", YELLOW, get_current_time()
				- data->start_time, data->index_of_philo, NC);
            // sleep
			ft_usleep(data->data->time_to_sleep); 
            // think
			printf("%s %zu %d is thinking%s\n", GREEN, (get_current_time()
					- data->start_time), data->index_of_philo, NC);
	}
}