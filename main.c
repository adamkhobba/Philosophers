/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:12:17 by adam              #+#    #+#             */
/*   Updated: 2024/07/14 16:14:30 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philosophers.h"

void ft_init_struct(char **av, int ac, t_philo *data)
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

int main (int ac, char **av)
{
    t_data data;
    t_data *pdata;
    int i;

    if (!ft_parsing(av, ac))
        return (1);
    pdata = &data;
    pdata->dead_flag = 1;
    i = 0;
    pdata->num_of_philos = ft_atoi(av[1]);
    pdata->philos = malloc(sizeof(t_philo) * (pdata->num_of_philos)); 
    printf("%screating of mutex %s\n", YELLOW, NC);
    while (i < pdata->num_of_philos)
    {
        ft_init_struct(av, ac, &data);
        if (pthread_mutex_init(&pdata->philos[i].forks, NULL))
            return (1); // freeing before exite the program 
        pdata->philos[i].forks_l = pdata->philos[(i + 1) % pdata->num_of_philos].forks;
        i++;
    }
    i = 0;
    while (i < pdata->num_of_philos)
    {
        pdata->philos[i].index_of_philo = i;
        if(pthread_create(&pdata->philos[i].thread, NULL, &ft_philos_routine, &pdata->philos[i]))
            return (1); // freeing before exite the program 
        i++;
    }
    i = 0;
    while (i < pdata->num_of_philos)
    {
        if (pthread_join(pdata->philos[i].thread,NULL))
            return (1); // freeing before exite the program
        i++;
    }
    i = 0;
    while (i < pdata->num_of_philos)
    {
        if (pthread_mutex_destroy(&pdata->philos[i].forks))
            return (1); // freeing before exite the program
        i++;
    }
    ft_free_data(pdata);
    return (0);
}
