/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:35:18 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/27 10:27:37 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_set_dead(t_data *data, int value)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		set(&data->philos[i].locker, &data->philos[i].dead, value);
		i++;
	}
}
