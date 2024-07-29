/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:14:39 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/29 12:23:56 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_stop(t_philo *data)
{
		if (data->last_meal == 0)
			return (1);
	return (0);
}
int	ft_all_kill(t_philo *data)
{
	int	i;
	pid_t pid;

	i = 0;
	pid = -1;
	while (i < data->data->num_of_philos)
	{
		if (i != data->index_of_philo)
			kill(data->data->pid[i], SIGKILL);
		else 
			pid = i;
		i++;
	}
	if (pid != -1)
		kill(pid, SIGKILL);
	return (0);
}

int	ft_check_dead(t_philo *data)
{
        if (get_current_time() - data->last_meal >= data->data->time_to_die)
        {
			printf("%s %zu %d died %s\n", RED, (get_current_time()
					- data->start_time), data->index_of_philo, NC);
			data->data->dead_flag = 0;
			// ft_all_kill(data);
			return (1);
        }
	return (0);
}

void    *ft_monitoring(void *args)
{
    t_philo	*data;

	data = (t_philo *)args;
	if (!ft_stop(data))
		ft_usleep(100);
	while (data->data->dead_flag)
	{
		if (ft_check_dead(data))
            return (NULL);
		// if (data->num_times_to_eat != -1
		// 	&& check_eat_time(data) == data->num_of_philos)
		// {
			// data->dead_flag = 0;
			// ft_set_dead(data, 0);
			// return (data->num_of_philos);
		// }
		// usleep(50);
	}
	return (NULL);
}