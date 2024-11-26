/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:00:56 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/16 16:33:18 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"

int	ft_conversion(char s, va_list *args)
{
	int	size;

	size = 0;
	if (s == 'c')
		size = ft_char(va_arg(*args, int));
	else if (s == 's')
		size = ft_str(va_arg(*args, char *));
	else if (s == 'p')
		size = ft_pointer(va_arg(*args, void *));
	else if (s == 'd' || s == 'i')
		size = ft_decimal(va_arg(*args, int));
	else if (s == 'u')
		size = ft_unsigned_decimal(va_arg(*args, unsigned int));
	else if (s == 'x')
		size = ft_hexa(va_arg(*args, unsigned int), "0123456789abcdef");
	else if (s == 'X')
		size = ft_hexa(va_arg(*args, unsigned int), "0123456789ABCDEF");
	else if (s == '%')
		size = write(1, "%", 1);
	return (size);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		ret;
	va_list	args;

	i = 0;
	ret = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			ret += ft_conversion(s[i], &args);
		}
		else
			ret += ft_char(s[i]);
		i++;
	}
	va_end(args);
	return (ret);
}
