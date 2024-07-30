/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:24:43 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/30 22:08:36by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_init_struct(char **av, int ac, t_data *data)
{
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
	if (pthread_create(&data->philos[i].thread, NULL, &ft_monitoring,
			&data->philos[i]) == -1)
		return (1);  
	ft_philos_routine(&data->philos[i]);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	pdata;
	int i;
	int *id;
	int	status;

	if (!ft_parsing(av, ac))
		return (1);
	// init data 
	pdata = (t_data){0};
	id = NULL;
	ft_init_struct(av, ac, &pdata);
	pdata.philos = (t_philo *)malloc(sizeof(t_philo) * (pdata.num_of_philos));
	if (!pdata.philos)
		return (1);
	id = (int *)malloc(sizeof(int) * pdata.num_of_philos);
	if (!id)
		return (ft_free(&pdata),1);
	memset(pdata.philos, 0, sizeof(t_philo) * pdata.num_of_philos);
	memset(id, 0, sizeof(int) * pdata.num_of_philos);
	pdata.id = id;
	ft_unlink();
	pdata.sem_print = sem_open("sem_print", O_CREAT, 0644, 1);
	if (pdata.sem_print == SEM_FAILED)
		return (1);
	if (pdata.num_times_to_eat % 2)
		pdata.forks = sem_open("forks", O_CREAT, 0644, pdata.num_of_philos + 1);
	else
		pdata.forks = sem_open("forks", O_CREAT, 0644, pdata.num_of_philos);
	if (pdata.forks == SEM_FAILED)
		return (1);
	i = 0; 
	id[i] = fork();
	while (i < pdata.num_of_philos - 1)
	{
		if (id[i++] != 0)
			id[i] = fork();
		else
			break;
	}
	if (id[i] == 0)
	{
		 if (ft_chlid_work(&pdata, i))
		 	return (1);
		return (0);
	}
		while(waitpid(-1, &status, 0) != -1)
		{
 			if (WEXITSTATUS(status) == 1)
				ft_kill(id, &pdata);
		}
		ft_free(&pdata);
	return (0);
}
