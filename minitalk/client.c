/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:13:51 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/04 20:10:17 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

int	ft_atoii(char *s)
{
	int	i;
	int	ret;
	int sign;

	sign = 1;
	ret = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		ret = (ret * 10) + (s[i] - 48);
		i++;
	}
	return (ret * sign);
}

void ft_atob(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		usleep(50);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoii(argv[1]);
		while (argv[2][i])
		{
			ft_atob(pid, argv[2][i]);
			i++;
		}
	}
	return (0);
}
