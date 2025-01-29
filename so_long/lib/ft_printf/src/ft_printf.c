/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:00:56 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/17 16:11:54 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"


int	ft_conversion(char s, va_list *args)
{
	int	c;

	c = 0;
	if (s == 'c')
		c = ft_char(va_arg(*args, int));
	else if (s == 's')
		c = ft_str(va_arg(*args, char *));
	else if (s == 'p')
		c = ft_pointer(va_arg(*args, void *));
	else if (s == 'd' || s == 'i')
		c = ft_decimal(va_arg(*args, int));
	else if (s == 'u')
		c = ft_unsigned_decimal(va_arg(*args, unsigned int));
	else if (s == 'x')
		c = ft_hexa(va_arg(*args, unsigned int), "0123456789abcdef");
	else if (s == 'X')
		c = ft_hexa(va_arg(*args, unsigned int), "0123456789ABCDEF");
	else if (s == '%')
		c = ft_char('%');
	return (c);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		c;

	i = 0;
	c = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			c += ft_conversion(s[i], &args);
		}
		else
			c += ft_char(s[i]);
		i++;
	}
	va_end(args);
	return (c);
}
