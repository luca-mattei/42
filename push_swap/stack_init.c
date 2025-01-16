/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:24:28 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/14 18:45:54 by lumattei         ###   ########.fr       */
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
    while (str[i] && (str[i] >= '0' && str[i <= '9']))
    {
        ret = ret * 10 + (str[i] - 48);
        i++;
    }
    return (ret * sign);
}

void	stack_init(t_stack_node **a, char **argv, bool flag_argc_2)
{
	long	nbr;
	int	i;

	i = 0;
	while (argv[i])
	{
		if (error_synthax(argv[i]))
			error_free(a, argv, flag_argc_2);
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			error_free(a, argv, flag_argc_2);
		if (error_repitiion(*a, (int)nbr))
			error_free(a, argv, flag_argc_2);
		append_node(a, (int)nbr);
		i++;
	}
	if (flag_argc_2)
		free_matrix(argv);
}
				
