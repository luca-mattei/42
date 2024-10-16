/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_decimal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:06:43 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/15 20:53:15 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/ft_printf.h"

static size_t	ft_uinumlen(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int c)
{
	size_t	len;
	char	*ret;

	len = ft_uinumlen(c);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	ret[len] = '\0';
	if (!ret)
		return (0);
	if (c == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	while (len > 0)
	{
		ret[--len] = (c % 10) + 48;
		c /= 10;
	}
	return (ret);
}

int ft_unsigned_decimal(unsigned int c)
{
	int		len;
	char	*ret;

	if (c == 0)
		return (write(1, "0", 1));
	ret = ft_uitoa(c);
	len = ft_strlen(ret);
	ft_putstr_fd(ret, 1);
	free(ret);
	return (len);
}
