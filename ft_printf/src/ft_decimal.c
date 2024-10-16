/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:36:19 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/16 12:16:30 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"

int ft_decimal(int c)
{
	size_t	size;
	char	*str;

	if (c == 0)
		return (write (1, "0", 1));
	str = ft_itoa(c);
	if (!str)
		return (0);
	ft_putstr_fd (str, 1);
	size = ft_strlen(str);
	free(str);
	return (size);	
}
