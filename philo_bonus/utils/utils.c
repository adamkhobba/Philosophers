/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:34:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/30 15:52:19 by akhobba          ###   ########.fr       */
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
    free(data->id);
    free(data->philos);
}