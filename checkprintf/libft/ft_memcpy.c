/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:38:15 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/06 17:38:54 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}
/*
#include <stdio.h>

int main(void)
{
	const unsigned char *src;
	unsigned char		dst[10];
	src = (unsigned char *)"test";
	ft_memcpy(dst, src, 3);
	printf("%s\n", dst);
	dst[3] = '\0';
	return (0);
}*/
