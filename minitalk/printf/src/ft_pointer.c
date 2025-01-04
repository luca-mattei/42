/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:59:17 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/30 17:06:52 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"

static void	ft_putnbr_base(unsigned long n, char *base)
{
	if (n >= 16)
		ft_putnbr_base(n / 16, base);
	write(1, &base[n % 16], 1);
}


int ft_pointer(void *ptr)
{
	unsigned long	i;
	unsigned long	adr;

	adr = (unsigned long)ptr;
	i = write(1, "0x", 2);
	if (adr == 0)
		i += write(1,"0", 1);
	else
	{
		ft_putnbr_base(adr, "0123456789abcdef");
		while (adr > 0)
		{
			adr /= 16;
			i++;
		}
	}
	return (i);
}
