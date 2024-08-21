/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:24:15 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/21 10:38:31 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->lock_print, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	while (i < data->num_of_philos)
	{
		if (i % 2 == 0)
		{
			data->philos[i].forks = &data->forks[i];
			data->philos[i].forks_l = &data->forks[(i + 1)
				% data->num_of_philos];
		}
		else
		{
			data->philos[i].forks_l = &data->forks[i];
			data->philos[i].forks = &data->forks[(i + 1)
				% data->num_of_philos];
		}
		pthread_mutex_init(&data->forks[i], NULL);
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
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return ;
	memset(data->forks, 0, sizeof(pthread_mutex_t) * data->num_of_philos);
}

int	ft_join(t_data *data)
{
	int	i;

	i = 0;
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
	pdata.num_of_philos = ft_atoi(av[1]);
	ft_init_struct(av, ac, &pdata);
	pdata.philos = (t_philo *)malloc(sizeof(t_philo) * (pdata.num_of_philos));
	if (!pdata.philos)
		return (1);
	memset(pdata.philos, 0, sizeof(t_philo) * pdata.num_of_philos);
	ft_init_mutex(&pdata);
	ft_creation_of_philo(&pdata);
	if (ft_monitoring(&pdata))
	{
		ft_join(&pdata);
		ft_free_mutex(&pdata, pdata.num_of_philos - 1);
		free(pdata.philos);
		return (1);
	}
	if (ft_join(&pdata))
		return (0);
	ft_free_mutex(&pdata, pdata.num_of_philos - 1);
	free(pdata.philos);
	return (0);
}
