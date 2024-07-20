/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:32:48 by adam              #+#    #+#             */
/*   Updated: 2024/07/16 11:52:08by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int ft_stop(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philos)
    {
        if (!data->philos[i].last_meal)
            return (0);
        i++;
    }
    return (1);
}

int ft_monitoring(void *arg)
{
    int i;
    t_data *data;

    data = (t_data *)arg;
    while (!ft_stop(data))
        ft_usleep(100);
    while (data->dead_flag)
    {
        i = 0;
        while(i < data->num_of_philos)
        {
            // printf("current = %zu\n", get_current_time() -
            //     data->philos[i].last_meal);
            if (get_current_time() - data->philos[i].last_meal >= data->time_to_die)
            {
                printf("%s %zu %d died %s\n", RED,
                (get_current_time() - data->philos[i].start_time),
            data->philos[i].index_of_philo, NC);
                return (1);
            }
            i++;
        }
            ft_usleep(data->time_to_die / 3);
    }
    return (0);
}