/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_playable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:36:32 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/28 21:37:21 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	init_visited_map(t_map *map)
{
	int	i;

	i = 0;
	map->visited = malloc(map->height * sizeof(char *));
	if (!map->visited)
		return (0);
	while (i < map->height)
	{
		map->visited[i] = malloc(map->width * sizeof(char));
		if (!map->visited[i])
		{
			while (--i >= 0)
				free(map->visited[i]);
			free(map->visited);
			return (0);
		}
		ft_memset(map->visited[i], false, map->width);
		i++;
	}
	return (1);
}

bool	flood_fill(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	if (map->visited[y][x] == true || map->grid[y][x] == '1'
		|| map->grid[y][x] == 'E')
	{
		if (map->grid[y][x] == 'E')
			map->exit_found = true;
		return (false);
	}
	map->visited[y][x] = true;
	if (map->grid[y][x] == 'C')
		map->collect_found++;
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
	return (map->exit_found);
}

int	check_map_playable(t_map *map)
{
	if (!init_visited_map(map))
		return (0);
	map->exit_found = flood_fill(map, map->player_x, map->player_y);
	free_map_visited(map);
	return (map->collect_found == map->collectibles && map->exit_found);
}
