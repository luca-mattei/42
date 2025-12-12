#include "../includes/cube3d.h"


void	free_config(t_config *config)
{
	int	i;

	if (config->north_texture)
		free(config->north_texture);
	if (config->south_texture)
		free(config->south_texture);
	if (config->west_texture)
		free(config->west_texture);
	if (config->east_texture)
		free(config->east_texture);
	if (config->map)
	{
		i = 0;
		while (config->map[i])
		{
			free(config->map[i]);
			i++;
		}
		free(config->map);
	}
}

void	print_error(const char *message)
{
	printf("Error: %s\n", message);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	ft_memset(&game.config, 0, sizeof(t_config));
	if (parse_config_file(argv[1], &game.config) != 0)
		return (free_config(&game.config), 1);
	if (validate_map(&game.config) != 0)
	{
		free_config(&game.config);
		return (1);
	}
	
	printf("Map loaded successfully!\n");
	printf("Map dimensions: %dx%d\n", game.config.map_width, game.config.map_height);
	
	// Nettoyage
	free_config(&game.config);
	
	return (0);
}