/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:12:11 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/04 16:11:39 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_src;
	size_t	len_dst;

	i = 0;
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	j = len_dst;
	if (dstsize == 0)
		return (len_src);
	if (dstsize < len_dst)
		return (dstsize + len_src);
	while (src[i] && (i + len_dst) < (dstsize - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[i + j] = '\0';
	return (len_dst + len_src);
}
/*
int main(void)
{
	char	dst[20] = "Ho ";
	const char	*src = "oui!";
//	size_t	i;
	ft_strlcat(dst, src, 0);
	printf("%s\n", dst);
//	printf("%lu\n", i);
	return (0);
}*/
