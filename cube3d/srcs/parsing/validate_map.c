// srcs/parsing/validate_map.c
#include "cube3d.h"

int	validate_map(t_config *config)
{
	int	i;
	int j;
    int player_count;

    i = 0;
    j = 0;
    player_count = 0;
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			if (!is_valid_map_char(config->map[i][j]))
				return (print_error("Invalid character in map"), 1);
			if (config->map[i][j] == 'N' || config->map[i][j] == 'S' || 
				config->map[i][j] == 'E' || config->map[i][j] == 'W')
			{
				config->spawn_x = j;
				config->spawn_y = i;
				config->spawn_dir = config->map[i][j];
				player_count++;
			}
			if (config->map[i][j] == '0' || config->map[i][j] == 'N' || 
				config->map[i][j] == 'S' || config->map[i][j] == 'E' || 
				config->map[i][j] == 'W')
			{
				if (i == 0 || i == config->map_height - 1 || 
					j == 0 || j == config->map_width - 1)
					return (print_error("Map not closed by walls"), 1);
				// Vérifie les cases adjacentes
				if (config->map[i-1][j] == ' ' || config->map[i+1][j] == ' ' ||
					config->map[i][j-1] == ' ' || config->map[i][j+1] == ' ')
					return (print_error("Map not closed by walls"), 1);
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (print_error("Map must have exactly one player"), 1);
	config->map[config->spawn_y][config->spawn_x] = '0';
	
	return (0);
}