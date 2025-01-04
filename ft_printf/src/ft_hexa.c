/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:56:27 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/15 21:09:34 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"

static void	ft_putnbr_base(unsigned int nbr, char *base)
{
	if (nbr >= 16)
		ft_putnbr_base(nbr / 16, base);
	write(1, &base[nbr % 16], 1);
}

int	ft_hexa(unsigned int nbr, char *base)
{
	size_t	i;

	i = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	ft_putnbr_base(nbr, base);
	while (nbr > 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}
