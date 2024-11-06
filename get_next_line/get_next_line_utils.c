/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:11:31 by lumattei          #+#    #+#             */
/*   Updated: 2024/11/06 16:33:14 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if ((unsigned char)c == '\0')
		return (&s[ft_strlen(s)]);
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == '\0')
		return (0);
	return (&s[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	while (s1 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}
