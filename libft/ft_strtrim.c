/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:59:58 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/08 00:23:08 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	*ft_tab(int	*tab, char const *set)
{
	int	i;

	i = 0;
	while (i <= 255)
		tab[i++] = 0;
	i = 0;
	while (set[i])
		tab[(int)set[i++]] = 1;
	return (tab);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		tab[256];
	size_t	start;
	size_t	end;
	char	*ret;

	if (!s1 || !set)
		return (0);
	ft_tab(tab, set);
	start = 0;
	while (s1[start] && tab[(int)s1[start]] == 1)
		start++;
	end = ft_strlen(s1);
	while (end > start && tab[(int)s1[end - 1]] == 1)
		end--;
	ret = malloc((end - start) + 1);
	if (!ret)
		return (0);
	ft_memcpy(ret, s1 + start, end - start);
	ret[end - start] = '\0';
	return (ret);
}
/*
int main(void)
{
	char const	*s1 = "8123481856781";
	char const	*s2 = "1278";
	printf("%s\n", ft_strtrim(s1, s2));
	return (0);
}*/
