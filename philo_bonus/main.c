/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:49:15 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/31 11:49:30 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_init_struct(char **av, int ac, t_data *data)
{
	ft_unlink();
	data->start_time = get_current_time();
	data->num_of_philos = ft_atoi(av[1]);
	data->dead_flag = 1;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_times_to_eat = ft_atoi(av[5]);
	else
		data->num_times_to_eat = -1;
}

int	ft_chlid_work(t_data *data, int i)
{
	data->sem_data = sem_open("sem_data", O_CREAT, 0644, 1);
	if (data->sem_data == SEM_FAILED)
		return (1);
	data->philos[i].index_of_philo = i + 1;
	data->philos[i].data = data;
	data->philos[i].last_meal = 0;
	data->philos[i].full = 0;
	if (pthread_create(&data->philos[i].thread, NULL, &ft_monitoring,
			&data->philos[i]) == -1)
		return (1);
	ft_philos_routine(&data->philos[i]);
	return (0);
}

int	ft_init_data(t_data pdata, t_philo **philos, int **id)
{
	*id = NULL;
	*philos = (t_philo *)malloc(sizeof(t_philo) * (pdata.num_of_philos));
	if (!*philos)
		return (1);
	*id = (int *)malloc(sizeof(int) * pdata.num_of_philos);
	if (!*id)
		return (1);
	memset(pdata.philos, 0, sizeof(t_philo) * pdata.num_of_philos);
	memset(*id, 0, sizeof(int) * pdata.num_of_philos);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	pdata;
	int		i;

	if (!ft_parsing(av, ac))
		return (1);
	ft_init_struct(av, ac, &pdata);
	ft_init_data(pdata, &pdata.philos, &pdata.id);
	ft_init_sem(pdata, &pdata.sem_print, &pdata.forks);
	i = 0;
	pdata.id[i] = fork();
	while (i < pdata.num_of_philos - 1)
	{
		if (pdata.id[i] != 0)
			pdata.id[++i] = fork();
		else
			break ;
	}
	if (pdata.id[i] == 0)
	{
		if (ft_chlid_work(&pdata, i))
			return (1);
		return (0);
	}
	ft_wait(pdata.id, &pdata);
	return (ft_free(&pdata), 0);
}
