/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:24:43 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/30 22:03:48 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_philos == 1)
		return (1);
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) == -1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_init_struct(char **av, int ac, t_data *data)
{
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
	ft_init_struct(av, ac, &pdata);
	pdata.philos = (t_philo *)malloc(sizeof(t_philo) * (pdata.num_of_philos));
	if (!pdata.philos)
		return (1);
	id = (int *)malloc(sizeof(int) * pdata.num_of_philos);
	if (!id)
		return (1);
	pdata.id = id;
	memset(pdata.philos, 0, sizeof(t_philo) * pdata.num_of_philos);
	memset(id, 0, sizeof(int) * pdata.num_of_philos);
	sem_unlink("forks"); 
	sem_unlink("sem_print");
	sem_unlink("sem_data");
	pdata.sem_print = sem_open("sem_print", O_CREAT, 0644, 1);
	if (pdata.sem_print == SEM_FAILED)
		return (1); // free before return 
	if (pdata.num_times_to_eat % 2)
		pdata.forks = sem_open("forks", O_CREAT, 0644, pdata.num_of_philos + 1);
	else
		pdata.forks = sem_open("forks", O_CREAT, 0644, pdata.num_of_philos);
	if (pdata.forks == SEM_FAILED)
		return (1); // free before return 
	// begin of the program
	i = 0; 
	pdata.start_time = get_current_time();
	id[i] = fork();
	while (i < pdata.num_of_philos - 1)
	{
		if (id[i] != 0)
		{
			i++;
			id[i] = fork();
		}
		else
			break;
	}
	if (id[i] == 0)
	{
		pdata.sem_data = sem_open("sem_data", O_CREAT, 0644, 1);
		if (pdata.sem_data == SEM_FAILED)
			return (1); // free before return
		pdata.philos[i].index_of_philo = i + 1;
		pdata.philos[i].data = &pdata;
		pdata.philos[i].last_meal = 0;
		if (pthread_create(&pdata.philos[i].thread, NULL, &ft_monitoring,
				&pdata.philos[i]) == -1)
			return (1); // free before return 
		ft_philos_routine(&pdata.philos[i]);
	}
	else
	{
		while(waitpid(-1, &status, 0) != -1)
		{
 			if (WEXITSTATUS(status) == 1)
			{
				ft_kill(id, &pdata);
				break;
			}
		}
		ft_free(&pdata);
	}
	return (0);
}
