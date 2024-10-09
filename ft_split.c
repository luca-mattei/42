/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:56:40 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/09 05:20:17 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_free_tab(char **tab, size_t n_tab)
{
	size_t	i;

	i = 0;
	while (i < n_tab)
		free(tab[i++]);
	free(tab);
}

static char	**ft_tab(char const *s, char c)
{
	size_t	i;
	size_t	tab_size;
	char	**tab;

	i = 0;
	tab_size = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab_size++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	tab = (char **)malloc(sizeof(char *) * (tab_size + 1));
	if (!tab)
		return (0);
	tab[tab_size] = NULL;
	return (tab);
}

static char	*ft_case(char const *s, size_t start, size_t end)
{
	char	*tab;
	size_t	j;

	j = 0;
	tab = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (!tab)
		return (0);
	while (start < end)
		tab[j++] = s[start++];
	tab[j] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	n_tab;
	size_t	start;
	size_t	i;

	n_tab = 0;
	start = 0;
	i = 0;
	tab = ft_tab(s, c);
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			tab[n_tab] = ft_case(s, start, i);
			if (!tab[n_tab++])
				return (ft_free_tab(tab, n_tab), NULL);
		}
	}
	return (tab);
}
/*
int main(void)
{
     char const     *s = "lorem ipsum dolor sit amet";
     char           c = ' ';
     char           **tab;
	int i = 0;
     tab  = ft_split(s, c);
	 while (tab[i])
	 {
		printf("%s\n", tab[i]);
		i++;
	 }
     return (0);
}*/
