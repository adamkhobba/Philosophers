/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lockvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:24:23 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/07 13:13:36 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set(pthread_mutex_t *locker, size_t *var, size_t value)
{
	pthread_mutex_lock(locker);
	*(size_t *)var = value;
	pthread_mutex_unlock(locker);
}

size_t	get(pthread_mutex_t *locker, size_t *var)
{
	size_t	res;

	pthread_mutex_lock(locker);
	res = *(size_t *)var;
	pthread_mutex_unlock(locker);
	return (res);
}
