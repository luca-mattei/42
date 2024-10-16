/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:26:38 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/08 03:43:57 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	size_t	i;

	i = ft_strlen(s1);
	s = malloc(i + 1);
	if (!s)
		return (0);
	ft_memcpy(s, s1, i);
	s[i] = '\0';
	return (s);
}
