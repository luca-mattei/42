/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:16:58 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/28 21:13:23 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long"

static void	put_element(t_game *game, int x, int y)
{
	if (map->grid[y][x] == '0')
		mlx_put_image_to_window(game->mlx, game->window, game->floor,
				x * game->img_size, y * game->img_size);
	if (map->grid[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->window, game->wall,
				x * game->img_size, y * game->img_size);
	if (map->grid[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->window, game->player,
				x * game->img_size, y * game->img_size);
	if (map->grid[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->window, game->collectible,
				x * game->img_size, y * game->img_size);
	if (map->grid[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->window, game->exit,
				x * game->img_size, y * game->img_size);
}

void	gen_map(t_game	*game)
{
	int	x;
	int	y;

	x = 0;
	y = -1;
	while (++y < game->map->height)
	{
		x = -1
		while (++x < game->map->width)
			put_element(game, x, y);
	}
}

void	*put_sprites(void *mlx, char *path)
{
	int		width;
	int		height;
	void	*img;

	width = 32;
	height = 3	2;
	img = mlx_xmp_file_to_image(mlx, path, &width, &height);
	if (!img)
		return (ft_printf("Error loading sprite: %s\n", path));
	return (img);
}

int	load_sprites(t_game *game)
{
	game->wall = put_sprites(game->mlx, "./sprites/wall.xpm");
	game->player = put_sprites(game->mlx, "./sprites/player.xpm");
	game->exit = put_sprites(game->mlx, "./sprites/exit.xpm");
	game->floor = put_sprites(game->mlx, "./sprites/floor.xpm");
	game->collectible = put_sprites(game->mlx, "./sprites/collectible.xpm");
	if (!game->wall || !game->player || !game->exit || !game->floor
		|| !game->collectible)
		return (0);
	return (1);
}
