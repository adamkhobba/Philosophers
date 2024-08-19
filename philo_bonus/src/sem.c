/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:03:44 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/18 15:19:06 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_sem_trywait(sem_t *sem)
{
	long int	sval;

	sval = sem->__align;
	if (sval == 0)
		return (0);
	sem_wait(sem);
	return (1);
}

long int	ft_sem_getvalue(sem_t *sem)
{
	long int	sval;

	sval = sem->__align;
	return (sval);
}
