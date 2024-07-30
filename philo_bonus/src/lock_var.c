/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:39:04 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/30 20:15:25 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers_bonus.h"


void set(t_data *data, size_t *var, size_t value)
{
    sem_wait(data->sem_data);
    *var = value;
    sem_post(data->sem_data);
}

size_t get(t_data *data, size_t *var)
{
    size_t tmp;
    sem_wait(data->sem_data);
    tmp = *var;
    sem_post(data->sem_data);
    return (tmp);
}