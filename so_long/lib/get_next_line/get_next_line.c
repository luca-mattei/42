/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:10:27 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/29 12:23:12 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*get_line(char *s)
{
	int		i;
	char	*line;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	return (line);
}

static char	*get_rest(char *s)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	rest = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s) - i + 1));
	if (!rest)
		return (NULL);
	j = 0;
	while (s[i])
		rest[j++] = s[i++];
	rest[j] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*line;
	char		*buf;
	size_t		nbyte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	nbyte = 1;
	while (!ft_strchr_gnl(s, '\n') && nbyte != 0)
	{
		nbyte = read(fd, buf, BUFFER_SIZE);
		if (nbyte < 0)
			return (free(buf), free(s), NULL);
		buf[nbyte] = '\0';
		s = ft_strjoin_gnl(s, buf);
	}
	if (nbyte == 0)
		return (free(buf), NULL);
	line = get_line(s);
	s = get_rest(s);
	return (line);
}

int main(void)
{
	char *s1 = "salut";
	char *s2 = " ca va";
	char *ret = ft_strjoin(s1, s2);
	printf("%s\n", ret);
	free(ret);
	return (0);
}
/*
int main(void)
{
	char *s;
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
	{
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
	}
	s = get_next_line(fd);
    printf("%s\n", s);
	s = get_next_line(fd);
    printf("%s\n", s);
	s = get_next_line(fd);
    printf("%s\n", s);
	s = get_next_line(fd);
    printf("%s\n", s);
    close(fd);
    return 0;
}
*/
/*
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free (line);
	}
	close(fd);
	return (0);
}*/
