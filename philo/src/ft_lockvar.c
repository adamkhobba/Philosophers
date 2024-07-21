/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lockvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:24:23 by akhobba           #+#    #+#             */
/*   Updated: 2024/07/21 19:27:55 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void get(pthread_mutex_t *locker, int *var, int value)
{
    pthread_mutex_lock(locker);
        *(int *)var = value;
    pthread_mutex_unlock(locker);
}

// void *set(pthread_mutex_t *locker, void *var, int value, char option)
// {
//     pthread_mutex_lock(locker);
//     if (option == 'i')
//         *(int *)var = value;
//     else if (option == 's')
//         *(size_t *)var = (size_t)value;
//     pthread_mutex_unlock(locker);
// }