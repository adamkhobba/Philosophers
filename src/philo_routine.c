/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:24:27 by adam              #+#    #+#             */
/*   Updated: 2024/07/14 18:23:10 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void ft_eat(t_philo *data)
{
    pthread_mutex_lock(data->forks_l); 
    printf("threar %d is taking a fork left\n", data->index_of_philo);
    pthread_mutex_lock(&data->forks);
    printf("threar %d is taking a fork right\n", data->index_of_philo);
    printf("thread %d is eating\n", data->index_of_philo);
    ft_usleep(data->time_to_eat);
    pthread_mutex_unlock(&data->forks);
    pthread_mutex_unlock(data->forks_l);
}
void *ft_philos_routine(void *args)
{
    t_philo *data;
    int i;
    
    i = 0;
    data = (t_philo *)args;
    if (data->index_of_philo % 2 == 0)
        ft_usleep(60);
    while (1)
    {
        //eat
        ft_eat(data);
        //sleep
        printf("thread %d is sleeping\n", data->index_of_philo); 
        ft_usleep(data->time_to_sleep);
        //think
        printf("thread %d is thinking\n", data->index_of_philo);
        // sleep(3);
        // pthread_mutex_lock(&data->philos[0].forks);
        // pthread_mutex_unlock(&data->philos[0].forks);
        i++;
    }
    return (NULL); 
}