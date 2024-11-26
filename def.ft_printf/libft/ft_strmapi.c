/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:34:49 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/10 21:56:51 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	char			*str;
	unsigned int	i;

	str = (char *)s;
	i = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ret)
		return (0);
	while (s[i])
	{
		ret[i] = f(i, str[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
