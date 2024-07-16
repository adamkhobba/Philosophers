/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:32:48 by adam              #+#    #+#             */
/*   Updated: 2024/07/15 17:08:53 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void *ft_monitoring(void *arg)
{
    int i;
    t_data *data;

    data = (t_data *)arg;
    while (data->dead_flag)
    {
        i = 0;
        while(i < data->num_of_philos)
        {
            printf("current = %zu\n", data->philos[i].current_meal -
                data->philos[i].last_meal);
            if (data->philos[i].current_meal - data->philos[i].last_meal >= data->time_to_die)
            {
                printf("thread %d is dead\n", data->philos[i].index_of_philo);
                return ((void *)1);
            }
            ft_usleep(100);
            i++;
        }
    }
    return (0);
}