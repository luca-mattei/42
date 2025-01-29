/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:11:06 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/10 17:09:22 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_tab_size(const char *s, char c)
{
	size_t	i;
	size_t	n_word;

	i = 0;
	n_word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			n_word++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (n_word);
}

static char	*ft_word(char const *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (0);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	itab;
	int		x;
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (ft_tab_size(s, c) + 1));
	if (!s || !tab)
		return (0);
	i = 0;
	itab = 0;
	x = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && x < 0)
			x = i;
		else if ((s[i] == c || s[i] == '\0') && x >= 0)
		{
			tab[itab++] = ft_word(s, x, i);
			x = -1;
		}
		i++;
	}
	tab[itab] = 0;
	return (tab);
}
/*
int main(void)
{
	char const *s = "12 34 45";
	char		c = ' ';
	char		**tab;
	size_t		i;

	i = 0;	
	tab = ft_split(s, c);
	while (tab[i])
		printf("%s\n", tab[i++]);
	return(0);
}*/
