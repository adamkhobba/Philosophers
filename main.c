/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:12:17 by adam              #+#    #+#             */
/*   Updated: 2024/07/13 19:06:26 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

void ft_init_struct(char **av, int ac, t_data *data)
{
    data->dead_flag = 1;
        data->time_to_die  = ft_atoi(av[2]);
        data->time_to_eat = ft_atoi(av[3]);
        data->time_to_sleep  = ft_atoi(av[4]);
        if (ac == 6)
            data->num_times_to_eat = ft_atoi(av[5]);
        else 
            data->num_times_to_eat = -1;
}

int main (int ac, char **av)
{
    pthread_t *philo_thread;
    t_data data;
    t_data *pdata;
    int i;

    if (!ft_parsing(av, ac))
        return (1);
    pdata = &data;
    ft_init_struct(av, ac, &data);
    printf("%screating of mutex %s\n", YELLOW, NC);
    i = 0;
    pdata->num_of_philos = ft_atoi(av[1]);
    philo_thread = malloc(sizeof(pthread_t) * (pdata->num_of_philos + 1)); 
    pdata->forks = malloc(sizeof(pthread_mutex_t) * pdata->num_of_philos);
    while (i < pdata->num_of_philos)
    {
        pthread_mutex_init(&pdata->forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < pdata->num_of_philos + 1)
    {
        pthread_create(&philo_thread[i], NULL, &ft_philos_routine, pdata);
        i++;
    }
    i = 0;
    while (i < pdata->num_of_philos + 1)
    {
        pthread_join(philo_thread[i],NULL);
        i++;
    }
    i = 0;
    while (i < pdata->num_of_philos)
    {
        pthread_mutex_destroy(&pdata->forks[i]);
        i++;
    }
    return (0);
}
