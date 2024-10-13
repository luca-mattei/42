/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:22:21 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/10 19:34:33 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_numlen(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	i;
	int		l;
	char	*ret;

	i = (long)n;
	l = ft_numlen(i);
	ret = (char *)malloc(sizeof(char) * (l + 1));
	if (!ret)
		return (0);
	ret[l] = '\0';
	if (i < 0)
	{
		ret[0] = '-';
		i = -i;
	}
	if (i == 0)
		ret[0] = '0';
	while (i > 0)
	{
		ret[--l] = (i % 10) + 48;
		i /= 10;
	}
	return (ret);
}
/*
int main(void)
{
	int n = 0;
	printf("%s\n", ft_itoa(n));
	return (0);
}*/
