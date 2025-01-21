/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:26:19 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/20 15:15:50 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static char	*get_next_word(char *str, char sp)
{
	static int	cursor;
	int			len;
	int			i;
	char			*next_str;

	len = 0;
	i = 0;
	while (str[cursor] == sp)
		++cursor;
	while (str[cursor + len] != sp && str[cursor + len])
		++len;
	next_str = (char *)malloc(sizeof(char) * (len + 1));
	if (next_str == NULL)
		return (NULL);
	while (str[cursor] != sp && str[cursor])
		next_str[i++] = str[cursor++];
	next_str[i] = '\0';
	return (next_str);
}

static int	count_words(char *str, char sp)
{
	bool	new_word;
	int	count;

	new_word = true;
	count = 0;
	while (*str)
	{
		while (*str == sp)
			++str;
		while (*str && *str != sp)
		{
			if (new_word)
			{
				++count;
				new_word = false;
			}
			++str;
		}
		new_word = true;
	}
	return (count);
}

char	**ft_split(char *str, char sp)
{
	int	i;
	int	word_number;
	char **vector_strs;

	i = 0;
	word_number = count_words(str, sp);
	vector_strs = (char **)malloc(sizeof(char *) * (word_number + 2)); // +2 pour mimic argv za le 0 aussi.
	if (NULL == vector_strs)
		return (NULL);
	while (word_number-- >= 0)
	{
		if (i == 0)
		{
			vector_strs[i] = (char *)malloc(sizeof(char));
			if (vector_strs[i] == NULL)
				return (NULL);
			vector_strs[i++][0] = '\0';
			continue ;
		}
		vector_strs[i++] = get_next_word(str, sp);
	}
	vector_strs[i] = NULL;
	return (vector_strs);
}
