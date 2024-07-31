/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:34:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/31 14:07:33 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_kill(int *id, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		kill(id[i], SIGKILL);
		i++;
	}
	return (1);
}

void	ft_free(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->sem_print);
	sem_close(data->sem_data);
	free(data->id);
	free(data->philos);
}

void	ft_wait(int *id, t_data *data)
{
	int	status;

	status = -1;
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 1)
			ft_kill(id, data);
	}
}

void	ft_unlink(void)
{
	sem_unlink("forks");
	sem_unlink("sem_print");
	sem_unlink("sem_data");
}

int	ft_init_sem(t_data data, sem_t **sem_print, sem_t **forks)
{
	*sem_print = sem_open("sem_print", O_CREAT, 0644, 1);
	if (*sem_print == SEM_FAILED)
		return (1);
	*forks = sem_open("forks", O_CREAT, 0644, data.num_of_philos);
	if (*forks == SEM_FAILED)
		return (1);
	return (0);
}
