/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:26:42 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/07 12:10:10 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_args_nbr(int c)
{
	if (c == 5 || c == 6)
		return (1);
	return (0);
}

int ft_checknum(char **str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (ft_num_agrs(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int ft_num_agrs(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && i == 0)
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
