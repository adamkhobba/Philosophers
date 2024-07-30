/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:14:39 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/30 17:58:48 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_check_dead(t_philo *philo)
{
        if ((get_current_time() - philo->last_meal) >= philo->data->time_to_die)
        {
			printf("time of die =%zu\n", (get_current_time() - philo->last_meal));
			printf("time to die =%zu\n", philo->data->time_to_die);
			sem_wait(philo->data->sem_print);
			printf("%s %zu %d died %s\n", RED, get_current_time() -
				philo->data->start_time, philo->index_of_philo, NC);
			return (1);
        }
	return (0);
}

void    *ft_monitoring(void *args)
{
    t_philo	*philo;

	philo = (t_philo *)args;
	philo->status = 0;
	// while (philo->last_meal == 0)
	// 	ft_usleep(60);
	while (philo->data->dead_flag)
	{
		if (ft_check_dead(philo))
		{
			philo->data->dead_flag = 0;
			philo->status = 1;
            return (NULL);
		}
		// if (data->num_times_to_eat != -1
		// 	&& check_eat_time(data) == data->num_of_philos)
		// {
			// data->dead_flag = 0;
			// ft_set_dead(data, 0);
			// return (data->num_of_philos);
		// }
		// ft_usleep(9);
	}
	return (NULL);
}
