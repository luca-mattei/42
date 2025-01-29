/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:08:15 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/29 12:17:12 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12
# endif

char		*get_next_line(int fd);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strchr_gnl(char *s, int c);
char		*ft_strjoin_gnl(char *s1, char *s2);

#endif
