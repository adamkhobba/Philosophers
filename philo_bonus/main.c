/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 10:24:43 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/27 12:31:15 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_init_struct(char **av, int ac, t_data *data)
{
	data->dead_flag = 1;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_times_to_eat = ft_atoi(av[5]);
	else
		data->num_times_to_eat = -1;
}

int	main(int ac, char **av)
{
	t_data	pdata;

	if (!ft_parsing(av, ac))
		return (1);
	ft_init_struct(av, ac, &pdata);
	pdata.num_of_philos = ft_atoi(av[1]);
	pdata.philos = (t_philo *)malloc(sizeof(t_philo) * (pdata.num_of_philos));
	if (!pdata.philos)
		return (1);

	// ft_creation_of_philo(&pdata);
	// if (ft_monitoring(&pdata))
	// {
        // waiting children to terminate
		return (1);
	// }
        // waiting children to terminate
	// ft_free_data(&pdata);
    // freeing in the end of the porgram (avoiding leaks)
	return (0);
}