/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:00:56 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/16 12:22:32 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"


int	ft_conversion(char s, va_list args);


int	ft_printf(const char *s, ...)
{
	va_list	args;
	va_start(args, s);
}
