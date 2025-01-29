/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_init_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:53:00 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/28 21:20:39 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_file_extension(char *filename)
{
	char	*ext;

	ext = strrchr(filename, '.');
	if (!ext)
		return (0);
	if (ext == ".ber")
		return (1);
	return (0);
}

int	stock_map_int_grid(t_map *map, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->grid[i] = line;
		line = get_next_line(fd);
		if (!line)
			return (close(fd), 0);
		i++;
	}
	close(fd);
	return (1);
}

t_map	*map_init(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	map->grid = NULL;
	map->visited = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->collectibles = 0;
	map->collect_found = 0;
	return (map);
}

int	check_width(t_map *map, char *line, int	current_width)
{
	if (current_width == 0 || line[0] == '\n' || !line)
		return (0);
	if (line[current_width - 1] == '\n')
		current_width--;
	if (map->width == 0)
		map->width = current_width;
	if (map->width != current_width)
		return (0);
	map->height++;
	return (1);
}

int	parse_map(t_map *map, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!check_width(map, line, ft_strlen(line)))
			return (free(line), close(fd), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (!stock_map_in_grid(map, filename))
		return (close(fd), 0);
	close(fd);
	return (1);
}
