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


int ft_monitoring(void *arg)
{
    int i;
    t_data *data;

    data = (t_data *)arg;
    while (data->dead_flag)
    {
        i = 0;
        while (!data->philos[i].last_meal)
            ft_usleep(100);
        i = 0;
        while(i < data->num_of_philos)
        {
            printf("current = %zu\n", get_current_time() -
                data->philos[i].last_meal);
            if (get_current_time() - data->philos[i].last_meal >= data->time_to_die)
            {
                printf("%sthread %d is dead%s\n", RED, data->philos[i].index_of_philo, NC);
                return (1);
            }
            ft_usleep(data->time_to_die / 3 );
            i++;
        }
    }
    return (0);
}