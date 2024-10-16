/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:51:07 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/15 21:56:22 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"

int	ft_str(char *str)
{
	int	i;

	if (!str)
		return (write(1, "(null)", 6));
	i = ft_strlen(str);
	write (1, str, i);
	return (i);
}
