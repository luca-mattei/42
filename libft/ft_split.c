/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:56:40 by lumattei          #+#    #+#             */
/*   Updated: 2024/10/08 04:35:03 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char **ft_tab(char const *s, char c)
{
     size_t    i;
     size_t    tab_size;
     char      **tab;
     
     i = 0;
     tab_size = 0;
     while (s[i] == c)
          i++;
     while (s[i])
     {
          if (s[i] == c && (i == 0 || s[i - 1] == c))
               tab_size++;
          i++;
     }
     tab =(char **)malloc(sizeof(char *) * (tab_size + 1)); 
     if (!tab)
          return (0);
     tab[tab_size] = NULL;
     return (tab);
}

char *ft_case(char const *s, size_t start, size_t end)
{
     char      *tab;
     size_t    j;

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
     char      **tab;
     size_t    n_tab;
     size_t    start;
     size_t    i;

     n_tab = 0;
     start = 0;
     i = 0;
     tab = ft_tab(s, c);
     while (s[i])
     {
          if (s[i] != c)
               if (start == 0 || s[i - 1] == c)
                    start = i;
          if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
               tab[n_tab++] = ft_case(s, start, i + 1);
          i++;
     }
     return (tab);
}
/*
int main(void)
{
     char const     *s = ",salut,ca,va";
     char           c = ',';
     char           **tab;
     tab  = ft_split(s, c);
     printf("%s\n", tab[0]);
     printf("%s\n", tab[1]);
     printf("%s\n", tab[2]);
     return (0);
}*/
