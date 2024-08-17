/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:34:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/17 20:00:57 by akhobba          ###   ########.fr       */
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
	sem_close(data->eatten);
	sem_close(data->kill_all);
	free(data->id);
	free(data->philos);
}

void	ft_wait(int *id, t_data *data)
{
	long int	eatten;

	eatten = 0;
	while (ft_sem_trywait(data->kill_all) == 0
		&& eatten != data->num_of_philos)
	{
		usleep(1 * 1000);
		eatten = ft_sem_getvalue(data->eatten);
	}
	if (eatten != data->num_of_philos)
		ft_kill(id, data);
}

// void	ft_wait(int *id, t_data *data)
// {
// 	int	status;

// 	status = -1;
// 	while (waitpid(-1, &status, 0) != -1)
// 	{
// 		printf("status = %d\n", WEXITSTATUS(status));
// 		if (WEXITSTATUS(status) == 1)
// 			ft_kill(id, data);
// 	}
// }

void	ft_unlink(void)
{
	sem_unlink("forks");
	sem_unlink("sem_print");
	sem_unlink("sem_data");
	sem_unlink("eatten");
	sem_unlink("kill_all");
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
