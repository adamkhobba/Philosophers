/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:45:44 by adam              #+#    #+#             */
/*   Updated: 2024/08/21 10:45:42 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_isnull(char **input, char c)
{
	int	i;

	i = 1;
	if (c == 5)
	{
		while (i < c)
		{
			if (ft_atoi(input[i]) == 0)
				return (0);
			i++;
		}
	}
	else
	{
		i = 1;
		while (i < c - 1)
		{
			if (ft_atoi(input[i]) == 0)
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_check_negative(char **input, int c)
{
	int	i;
	int	j;

	i = 1;
	while (i < c)
	{
		j = 0;
		if (input[i][j] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_max(char **input, int c)
{
	int	i;

	i = 1;
	while (i < c)
	{
		if (ft_strlen(input[i]) > 10)
			return (0);
		if (ft_atoi(input[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	ft_parsing(char **input, int c)
{
	if (!ft_isnull(input, c))
	{
		printf("ERROR: invalid input\n");
		return (0);
	}
	if (!ft_check_negative(input, c))
	{
		printf("ERROR: negative numbers are not allowed\n");
		return (0);
	}
	if (!ft_check_max(input, c))
	{
		printf("ERROR: numbers are too big\n");
		return (0);
	}
	if (ft_checknum(input))
	{
		printf("ERROR: invalid input\n");
		return (0);
	}
	if (!ft_args_nbr(c))
		return (0);
	return (1);
}
