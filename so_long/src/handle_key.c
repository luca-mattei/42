#include "../inc/so_long.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free(game->mlx);
	exit(0);
	return (0);
}

void	display_moves(t_game *game)
{
	char	*moves_str;

	moves_str = ft_itoa(game->moves);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "Moves: ");
	mlx_string_put(game->mlx, game->win, 70, 20, 0xFFFFFF, moves_str);
	free(moves_str);
}

int	check_next_position(t_game *game, int next_y, int next_x)
{
	char	next_pos;

	next_pos = game->map->grid[next_y][next_x];
	if (next_pos == '1')
		return (1);
	if (next_pos == 'C')
	{
		game->collected++;
		game->map->grid[next_y][next_x] = '0';
	}
	if (next_pos == 'E')
	{
		if (game->collected == game->map->collectibles)
		{
			free_sprites(game);
			mlx_destroy_window(game->mlx, game->win);
			mlx_destroy_display(game->mlx);
			free(game->mlx);
			free_map(game->map);
			exit(1);
		}
		return (1);
	}
	return (0);
}

void	move_player(t_game *game, int new_y, int new_x)
{
	if (!check_next_position(game, new_y, new_x))
	{
		game->map->grid[game->map->player_y][game->map->player_x] = '0';
		game->map->grid[new_y][new_x] = 'P';
		game->map->player_x = new_x;
		game->map->player_y = new_y;
		ft_printf("Moves: %d\n", game->moves);
		game->moves++;
		draw_map(game);
		display_moves(game);
	}
}
