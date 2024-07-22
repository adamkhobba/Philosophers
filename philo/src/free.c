/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:23:54 by adam              #+#    #+#             */
/*   Updated: 2024/07/22 16:16:10 by akhobba          ###   ########.fr       */
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
	while (i < lim + 1)
	{
		if (pthread_mutex_destroy(&data->philos[i].forks))
			return (1);
		if (pthread_mutex_destroy(&data->philos[i].locker))
			return (1);
		i++;
	}
	return (0);
}
