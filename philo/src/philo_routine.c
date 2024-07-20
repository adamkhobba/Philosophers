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
    pthread_mutex_lock(&data->forks);
    data->last_meal = get_current_time();
    // if (data->dead)
        printf("%s %zu %d has taken a fork\n%s", BLUE,
            get_current_time() - data->start_time, data->index_of_philo, NC);
    // if (data->dead)
        printf("%s %zu %d is eating\n%s", CYAN, 
            get_current_time() - data->start_time, data->index_of_philo, NC);
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
    data->last_meal = get_current_time();
    while (data->data->dead_flag)
    {
        ft_eat(data);
        // if (data->dead)
            printf("%s %zu %d is sleeping\n%s", YELLOW,
                get_current_time() - data->start_time, data->index_of_philo, NC);
        ft_usleep(data->data->time_to_sleep);
        // if(data->dead)
            printf("%s %zu %d is thinking%s\n", GREEN,
                (get_current_time() - data->start_time), data->index_of_philo, NC);
        i++;
    }
    return (NULL);
}