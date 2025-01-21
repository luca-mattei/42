/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:24:28 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/20 17:15:28 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long  ft_atol(char *str)
{
    long     ret;
    int     i;
    int     sign;

    sign = 1;
    i = 0;
    ret = 0;
    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
        i++;
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
    {
	    sign *= -1;
	    i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        ret = ret * 10 + (str[i] - 48);
        i++;
    }
    return (ret * sign);
}

#include <stdio.h>

void	stack_init(t_stack_node **a, char **argv)
{
	long	nbr;
	int	i;

	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			error_free(a);
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			error_free(a);
		if (error_repetition(*a, (int)nbr))
			error_free(a);
		append_node(a, (int)nbr);
		i++;
	}
}	
