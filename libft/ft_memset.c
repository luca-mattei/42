/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:57:31 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/03 22:59:30 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}
/*
int main(void)
{
	char			b[21];
	ft_memset(b, 'A', 10);
	b[10] = '\0';
	printf("%s\n", b);
	ft_memset(b + 10, 'B', 10);
	b[20] = '\0';
	printf("%s\n", b);
	return (0);
}*/
