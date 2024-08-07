/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:23:54 by adam              #+#    #+#             */
/*   Updated: 2024/08/07 15:55:34 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free_data(t_data *data)
{
	free(data->philos);
}

int	ft_free_mutex(t_data *data, int lim)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->lock_print);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < lim + 1)
	{
		pthread_mutex_destroy(data->philos[i].forks);
		pthread_mutex_destroy(&data->philos[i].locker);
		i++;
	}
	free(data->forks);
	return (0);
}
