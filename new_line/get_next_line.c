/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:45:07 by lumattei          #+#    #+#             */
/*   Updated: 2024/11/23 15:55:28 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*ft_line(char *s)
{
	int		i;
	char	*line;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	return (line[i] = '\0', line);
}

static char	*ft_reste(char *s)
{
	int		i;
	int		j;
	char	*reste;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
		return (ft_free_ptr(&s), NULL);
	reste = (char *)malloc(sizeof(char) * (ft_strlen(s) - i));
	if (!reste)
		return (ft_free_ptr(&s), NULL);
	i++;
	while (s[i])
		reste[j++] = s[i++];
	reste[j] = '\0';
	return (ft_free_ptr(&s), reste);
}

char	*get_next_line(int fd)
{
	static char	*s;	
	char		*line;
	char		*buf;
	int			nbyte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	nbyte = 1;
	while (nbyte > 0 && !ft_strchr(s, '\n'))
	{
		nbyte = read(fd, buf, BUFFER_SIZE);
		if (nbyte == -1)
			return (ft_free_ptr(&buf), ft_free_ptr(&s), NULL);
		buf[nbyte] = '\0';
		s = ft_strjoin(s, buf);
	}
	if (!s || *s == '\0')
		return (ft_free_ptr(&buf), ft_free_ptr(&s), NULL);
	line = ft_line(s);
	s = ft_reste(s);
	return (ft_free_ptr(&buf), line);
}
/*
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	char *line;
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
	return (0);
}

while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
		}
	close(fd);
	return (0);
}*/
