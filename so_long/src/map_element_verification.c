/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_element_verification.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:26:02 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/28 21:35:47 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	perimeter_walls(t_map *map)
{
	int	i;
	int	height;
	int	width;

	i = 0;
	width = map->width;
	height = map->height - 1;
	if (height <= 1)
		return (0);
	while (i < width)
	{
		if (map->grid[0][i] != '1'
			|| map->grid[height][i] != '1')
			return (0);
		i++;
	}
	while (height)
	{
		if (map->grid[height][0] != '1'
			|| map->grid[height][width - 1] != '1')
			return (0);
		height--;
	}
	return (1);
}
int	set_exit(t_map *map, int y, int x)
{
	map->exit_x = x;
	map->exit_y = y;
	return (1);
}

int	set_player(t_map *map, int y, int x)
{
	map->player_x = x;
	map->player_y = y;
	return (1);
}

int	check_c(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'C')
				map->collectibles++;
			x++;
		}
		y++;
	}
	return (map->collectibles);
}

int	check_ep(t_map *map)
{
	int	y;
	int	x;
	int	count_e;
	int	count_p;

	y = -1;
	count_e = 0;
	count_p = 0;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (!ft_strchr("EPC10", map->grid[y][x]))
				return (0);
			if (map->grid[y][x] == 'E')
				count_e += set_exit(map, y, x);
			if (map->grid[y][x] == 'P')
				count_p += set_player(map, y, x);
		}
	}
	if (count_e == 1 && count_p == 1)
		return (1);
	return (0);
}
