/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:20:15 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/03 23:02:40 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	if (n != 0)
		ft_memset(s, '\0', n);
}
/*
#include <stdio.h>

int	main(void)
{
	unsigned char	b[20];
	ft_bzero(b, 10);
	b[10] = '\0';
	printf("%s\n", b);
	return (0);
}*/
