/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:12:17 by adam              #+#    #+#             */
/*   Updated: 2024/07/15 16:49:07 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_creation_of_philo(t_data *data)
{
    int i; 

    i = 0;
    while (i < data->num_of_philos)
    {
        if (pthread_mutex_init(&data->philos[i].forks, NULL))
            return (1); // freeing before exite the program 
        data->philos[i].forks_l = &data->philos[(i + 1) % data->num_of_philos].forks;
        i++;
    }
    i = 0;
    while (i < data->num_of_philos)
    {
        data->philos[i].data = data;
        if(pthread_create(&data->philos[i].thread, NULL,
            &ft_philos_routine, &data->philos[i]))
            return (1); // freeing before exite the program 
        data->philos[i].index_of_philo = i;
        i++;
    }
    return (0);
}

void ft_init_struct(char **av, int ac, t_data *data)
{
        data->time_to_die  = ft_atoi(av[2]);
        data->time_to_eat = ft_atoi(av[3]);
        data->time_to_sleep  = ft_atoi(av[4]);
        if (ac == 6)
            data->num_times_to_eat = ft_atoi(av[5]);
        else 
            data->num_times_to_eat = -1;
}

void ft_free_data(t_data *data)
{
    free(data->philos);
}
int ft_free_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philos)
    {
        if (pthread_mutex_destroy(&data->philos[i].forks))
            return (1); // freeing before exite the program
        i++;
    }
    return (0);
}
int main (int ac, char **av)
{
    t_data data;
    t_data *pdata;
    pthread_t monitor;
    int i;

    if (!ft_parsing(av, ac))
        return (1);    
    pdata = &data;
    ft_init_struct(av, ac, pdata);
    pdata->dead_flag = 1;
    pdata->num_of_philos = ft_atoi(av[1]);
    pdata->philos = malloc(sizeof(t_philo) * (pdata->num_of_philos));
    printf("%screating of mutex %s\n", YELLOW, NC);
    ft_creation_of_philo(pdata);
    if(pthread_create(&monitor, NULL, &ft_monitoring,pdata))
        return (1); // freeing before exite the program 
    i = 0;
    while (i < pdata->num_of_philos)
    {
        if (pthread_join(pdata->philos[i].thread,NULL))
            return (1); // freeing before exite the program
        i++;
    }
    if (pthread_join(monitor, NULL))
        return (1); // freeing before exite the program
    ft_free_mutex(pdata);
    ft_free_data(pdata);
    return (0);
}
