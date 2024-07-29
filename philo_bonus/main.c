/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:24:43 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/29 17:05:06 by akhobba          ###   ########.fr       */
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
	data->dead_flag = 1;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_times_to_eat = ft_atoi(av[5]);
	else
		data->num_times_to_eat = -1;
}

int	ft_kill(int *id, t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		printf("killing %d\n", id[i]);
		kill(id[i], SIGKILL);
		i++;
	}
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
	ft_init_struct(av, ac, &pdata);
	pdata.num_of_philos = ft_atoi(av[1]);
	pdata.philos = (t_philo *)malloc(sizeof(t_philo) * (pdata.num_of_philos));
	if (!pdata.philos)
		return (1);
	id = (int *)malloc(sizeof(int) * pdata.num_of_philos);
	if (!id)
		return (1);
	memset(pdata.philos, 0, sizeof(t_philo) * pdata.num_of_philos);
	memset(id, 0, sizeof(int) * pdata.num_of_philos);
	sem_unlink("sem"); 
	// begin of the program
	if (pdata.num_times_to_eat % 2)
		pdata.sem = sem_open("sem", O_CREAT, 0644, pdata.num_of_philos + 1);
	else
		pdata.sem = sem_open("sem", O_CREAT, 0644, pdata.num_of_philos);
	if (pdata.sem == SEM_FAILED)
		return (1);
	i = 0; 
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
		pdata.philos[i].index_of_philo = i + 1;
		pdata.philos[i].data = &pdata;
		pdata.philos[i].start_time = get_current_time();
		pdata.philos[i].last_meal = 0;
		if (pthread_create(&pdata.philos[i].thread, NULL, &ft_monitoring,
				&pdata.philos[i]) == -1)
			return (1);
		ft_philos_routine(&pdata.philos[i]);
		if (pthread_join(pdata.philos[i].thread, NULL) == -1)
			return (1);
		exit(pdata.philos[i].status);
	}
	else
	{
		i = 0;
		while(waitpid(id[i++], &status, 0) != -1)
		{
			if (status)	
				ft_kill(id, &pdata);
		}
	}
	free(id);
	free(pdata.philos);
	// ft_free_data(&pdata);
    // freeing in the end of the porgram (avoiding leaks)
	return (0);
}
