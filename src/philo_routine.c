/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:24:27 by adam              #+#    #+#             */
/*   Updated: 2024/07/14 16:20:45 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void ft_eat(t_philo *data)
{
    pthread_mutex_lock(&data->forks_l); 
    pthread_mutex_lock(&data->forks);
    ft_usleep(data->time_to_eat);
    pthread_mutex_unlock(&data->forks);
    pthread_mutex_unlock(&data->forks_l);
}
void *ft_philos_routine(void *args)
{
    t_philo *data;
    pthread_t tid;
    int i;
    
    i = 0;
    data = (t_philo *)args;
    tid = pthread_self();
    while (i < 3)
    {
        //eat
        ft_eat(data);
        ft_usleep(data->time_to_sleep);
        printf("thread %d is thinking\n", data->index_of_philo);
        // pthread_mutex_lock(&data->philos[0].forks);
        // pthread_mutex_unlock(&data->philos[0].forks);
        i++;
    }
    return (NULL); 
}