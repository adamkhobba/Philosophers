/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:14:39 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/06 18:04:36 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_check_dead(t_philo *philo)
{
	if ((get_current_time() - get(philo->data,
				&philo->last_meal)) > philo->data->time_to_die)
	{
		sem_wait(philo->data->sem_print);
		set(philo->data, &philo->data->dead_flag, 0);
		printf("%s %zu %d died %s\n", RED, get_current_time()
			- philo->data->start_time, philo->index_of_philo, NC);
		return (1);
	}
	return (0);
}

void	*ft_monitoring(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	philo->status = 0;
	while (get(philo->data, &philo->last_meal) == 0)
		usleep(600);
	while (get(philo->data, &philo->data->dead_flag))
	{
		if (ft_check_dead(philo))
		{
			philo->status = 1;
			break ;
		}
		if (philo->data->num_times_to_eat != -1
			&& philo->full >= (size_t)philo->data->num_times_to_eat)
		{
			set(philo->data, &philo->data->dead_flag, 0);
			philo->status = 0;
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
