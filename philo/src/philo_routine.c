/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:24:27 by adam              #+#    #+#             */
/*   Updated: 2024/07/15 11:12:49by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_eat(t_philo *data)
{
    pthread_mutex_lock(data->forks_l); 
    printf("threar %d is taking a fork left\n", data->index_of_philo);
    pthread_mutex_lock(&data->forks);
    printf("threar %d is taking a fork right\n", data->index_of_philo);
    data->last_meal = data->current_meal;
    data->current_meal = get_current_time();
    
    printf("thread %d is eating\n", data->index_of_philo);
    ft_usleep(data->data->time_to_eat);
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
    data->current_meal = get_current_time();
    while (data->data->dead_flag)
    {
        //eat
        ft_eat(data);
        //sleep
        printf("%sthread %d is sleeping\n%s", YELLOW, data->index_of_philo , NC);
        ft_usleep(data->data->time_to_sleep);
        //think
        printf("%sthread %d is thinking%s\n", GREEN, data->index_of_philo, NC);
        // sleep(2);
        i++;
    }
    return (NULL);
}