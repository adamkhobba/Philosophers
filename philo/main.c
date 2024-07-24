/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:24:15 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/23 17:09:44 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->philos[i].forks, NULL)
			|| pthread_mutex_init(&data->philos[i].locker, NULL))
		{
			ft_free_mutex(data, i);
			return (1);
		}
		data->philos[i].forks_l = &data->philos[(i + 1)
			% data->num_of_philos].forks;
		data->philos[i].full = 0;
		i++;
	}
	return (0);
}

int	ft_creation_of_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].start_time = get_current_time();
		data->philos[i].data = data;
		data->philos[i].index_of_philo = i + 1;
		if (pthread_create(&data->philos[i].thread, NULL, &ft_philos_routine,
				&data->philos[i]) == -1)
		{
			ft_free_mutex(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_init_struct(char **av, int ac, t_data *data)
{
	data->dead_flag = 1;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_times_to_eat = ft_atoi(av[5]);
	else
		data->num_times_to_eat = -1;
}

int	ft_join(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_philos == 1)
		return (1);
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) == -1)
		{
			ft_free_mutex(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	pdata;

	if (!ft_parsing(av, ac))
		return (1);
	ft_init_struct(av, ac, &pdata);
	pdata.num_of_philos = ft_atoi(av[1]);
	pdata.philos = (t_philo *)malloc(sizeof(t_philo) * (pdata.num_of_philos));
	if (!pdata.philos)
		return (1);
	ft_init_mutex(&pdata);
	ft_creation_of_philo(&pdata);
	if (ft_monitoring(&pdata))
	{
		if (ft_join(&pdata))
			return (1);
		return (1);
	}
	if (ft_join(&pdata))
		return (0);
	ft_free_mutex(&pdata, pdata.num_of_philos - 1);
	ft_free_data(&pdata);
	return (0);
}
