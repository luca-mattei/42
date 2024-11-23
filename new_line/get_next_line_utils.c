/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:10:14 by lumattei          #+#    #+#             */
/*   Updated: 2024/11/23 15:51:35 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return (&s[ft_strlen(s)]);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == '\0')
		return (NULL);
	return (&s[i]);
}

void	ft_free_ptr(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	if (!s2)
		return (s1);
	i = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (free(s1), NULL);
	ret[i] = '\0';
	i = 0;
	while (s1 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	return (free(s1), ret);
}
