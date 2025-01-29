/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:11:31 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/29 12:18:06 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strch_gnl(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if ((unsigned char)c == '\0')
		return (&s[ft_strlen_gnl(s)]);
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == '\0')
		return (0);
	return (&s[i]);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	size_t	lens1;
	size_t	lens2;

	if (!s2)
		return (s1);
	lens1 = ft_strlen_gnl(s1);
	lens2 = ft_strlen_gnl(s2);
	ret = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i++ < lens1)
		ret[i] = s1[i];
	i = 0;
	while (i++ < lens2)
		ret[lens1 + i] = s2[i];
	ret[lens1 + lens2] = '\0';
	return (ret);
}
