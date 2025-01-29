/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:18:31 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/01 16:48:39 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*
#include <stdio.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	(void)argc;
	printf("%d\n", ft_isdigit(argv[1][0]));
	printf("%d\n", ft_isdigit(argv[1][0]));
	return (0);
}*/
