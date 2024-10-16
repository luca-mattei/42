/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:29:47 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/08 04:19:25 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (start >= ft_strlen(s))
	{
		ret = malloc(sizeof(char));
		if (!ret)
			return (0);
		ret[0] = '\0';
		return (ret);
	}
	while (i < len && s[start + i])
		i++;
	ret = malloc(i + 1);
	if (!ret)
		return (0);
	ft_memcpy(ret, (s + start), i);
	ret[i] = '\0';
	return (ret);
}
/*
int main(void)
{
	char const		*s = "salut comment ca va";
	unsigned int	i = 30;
	printf("%s\n", ft_substr(s, i, 6));
	return (0);
}


	while (s[i] && (unsigned int)s[i] != start)
		i++;
	if ((unsigned int)s[i] == start)
	{
		while (j <= len && s[i + j])
			j++;
	}
	ret = malloc(j + 1);
	ft_memcpy(ret, s, j);
	ret[j] = '\0';
	return (ret);
}*/
