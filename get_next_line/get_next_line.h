/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:08:15 by lumattei          #+#    #+#             */
/*   Updated: 2024/11/06 16:40:48 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <fcntl.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 12
#endif

char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_strchr(char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
