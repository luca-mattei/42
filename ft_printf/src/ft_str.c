/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:51:07 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/17 16:04:21 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"

int	ft_str(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	return (write (1, str, ft_strlen(str)));
}
