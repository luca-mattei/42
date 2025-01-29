/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:31:48 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/29 11:36:18 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

int	init_game(t_game *game, t_map *map)
{
	game->img_size = 32;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->window = mlx_new_window(game->mlx, map->width * game->img_size,
			map->height * game -> img_size, "so long");
	if (!game->win)
		return (0);
	game->map = map;
	game->moves = 1;
	game->collected = 0;
	if (!load_sprites(game))
		return (free_sprites(game), 0);
	gen_map(game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
	return (1);
}
int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		free_sprites(game);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(game->map);
		exit(0);
	}
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, game->map->player_y - 1, game->map->player_x);
	if (keycode == KEY_S || keycode = KEY_DOWN)
		move_player(game, game->map->player_y + 1, game->map->player_x);
	if (keycode == KEY_A || keycode = KEY_LEFT
		move_player(game, game->map->player_y, game->map->player_x - 1);
	if (keycode == KEY_D || KEY_RIGHT)
		move_player(game, game->map->player_y, game->map->player_x + 1);
	return (0);
}
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (printf("Error\nUsage: ./so_long <path/to/map.ber>\n"), 1);
	map = init_map();
	if (!check_map(map, argv[1]))
		return (free_map(map), 1);
	ft_printf("Map successfully parsed!\n");
	if (!init_game(&game, map))
		return (free_map(map), 1);

