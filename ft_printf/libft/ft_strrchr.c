/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:38 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/06 18:26:36 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0 && s[i] != (unsigned char)c)
		i--;
	if (i == -1)
		return (0);
	return ((char *)&s[i]);
}
/*
int	main(void)
{
	const char	*s = "salut";
	int c = 'x';
	printf("%s\n", ft_strrchr(s, c));
	return (0);
}*/
