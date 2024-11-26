/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:35:45 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/04 03:56:10 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = ft_strlen(src);
	if (dstsize == 0)
		return (ret);
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ret);
}
/*
int	main(void)
{
	char	s1[20];
	char	*s2 = "salut";
	ft_strlcpy(s1, s2, 4);
//	strlcpy(s1, s2, 4);
	printf ("%s\n", s1);
	return (0);
}*/
