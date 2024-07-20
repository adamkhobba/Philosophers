/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:45:44 by adam              #+#    #+#             */
/*   Updated: 2024/07/20 17:05:42 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_args_nbr(int c )
{
    if (c == 5 || c == 6)
        return (1);
    return (0);
}

int ft_isdigit(int c)
{
    if (c >= 48 && c <= 57)
        return (1);
    return (0);
}

int ft_big_isdigit(char **input, int ac)
{
    int i;
    int j;

    i = 1;
    while (i < ac)
    {
        j = 0;
        while (input[i][j])
        {
            if (!ft_isdigit(input[i][j]))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}
int ft_isnull(char **input, char c)
{
    int i;

    i = 1;
    if (c == 5)
        while (i < c)
        {
            if (ft_atoi(input[i]) == 0)
                return (0);
            i++;
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

int ft_check_negative(char **input, int c)
{
    int i;
    int j;

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

int ft_check_max(char **input, int c)
{
    int i;

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

int ft_parsing(char **input, int c)
{
    if (!ft_args_nbr(c))
        return (0);
    if (!ft_big_isdigit(input, c))
        return (0);
    if (!ft_isnull(input, c))
        return (0);
    if (!ft_check_negative(input, c))
        return (0);
    if (!ft_check_max(input, c))
        return (0);
    return (1);
}
