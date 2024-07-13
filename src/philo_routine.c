/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:24:27 by adam              #+#    #+#             */
/*   Updated: 2024/07/13 16:05:04 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


void *ft_philos_routine(void *args)
{
    t_data *data;

    data = (t_data *)args;
    while (data->dead_flag)
    {
        pthread_mutex_lock(&data->philos->forks[0]);
        pthread_mutex_unlock(&data->philos->forks[0]);
    }
    return (NULL); 
}