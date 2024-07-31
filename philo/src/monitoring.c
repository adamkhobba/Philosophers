/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:15:03 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/31 11:55:29 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_stop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (!get(&data->philos[i].locker, &data->philos[i].last_meal))
			return (0);
		i++;
	}
	return (1);
}

int	check_eat_time(t_data *data)
{
	int	i;
	int	num_eated;

	i = 0;
	num_eated = 0;
	while (i < data->num_of_philos)
	{
		if (get(&data->philos[i].locker,
				&data->philos[i].full) >= (size_t)data->num_times_to_eat)
			num_eated++;
		i++;
	}
	return (num_eated);
}

int	ft_check_dead(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		if (get_current_time() - get(&data->philos[i].locker,
				&data->philos[i].last_meal) >= data->time_to_die)
		{
			data->dead_flag = 0;
			ft_set_dead(data, 0);
			printf("%s %zu %d died %s\n", RED, (get_current_time()
					- data->philos[i].start_time),
				data->philos[i].index_of_philo, NC);
			return (1);
		}
	}
	return (0);
}

int	ft_monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!ft_stop(data))
		ft_usleep(100);
	while (data->dead_flag)
	{
		if (ft_check_dead(data))
			return (data->num_of_philos);
		if (data->num_times_to_eat != -1
			&& check_eat_time(data) == data->num_of_philos)
		{
			data->dead_flag = 0;
			ft_set_dead(data, 0);
			return (data->num_of_philos);
		}
		usleep(500);
	}
	return (0);
}
