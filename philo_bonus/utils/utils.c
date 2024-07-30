/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:34:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/30 22:46:39 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_kill(int *id, t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		    kill(id[i], SIGKILL);
		i++;
	}
    return (1);
}
void ft_free(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->sem_print);
	sem_close(data->sem_data);
    free(data->id);
    free(data->philos);
}

void ft_unlink(void)
{
	sem_unlink("forks"); 
	sem_unlink("sem_print");
	sem_unlink("sem_data");
}

int	ft_init_pointers(t_philo *philo, int *id, t_data *data)
{
	philo = (t_philo *)malloc(sizeof(t_philo) * (data->num_of_philos));
	if (!philo)
		return (1);
	id = (int *)malloc(sizeof(int) * data->num_of_philos);
	if (!id)
		return (1);
	memset(philo, 0, sizeof(t_philo) * data->num_of_philos);
	memset(id, 0, sizeof(int) * data->num_of_philos);
	return (0);
}

int ft_init_sem(sem_t **sem, char *name, int value)
{
	*sem = sem_open(name, O_CREAT, 0644, value);
	if (*sem == SEM_FAILED)
		return (1);
	return (0);
}