// srcs/parsing/parse_map.c
#include "cube3d.h"

static int	get_max_line_length(char **map_lines)
{
	int	max_len;
	int	len;
	int	i;

	max_len = 0;
	i = 0;
	while (map_lines[i])
	{
		len = ft_strlen(map_lines[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

static int	count_map_lines(char **map_lines)
{
	int	count;

	count = 0;
	while (map_lines[count])
		count++;
	return (count);
}

int normalize_map(char **map_lines, t_config *config)
{
    int	i;
	int	j;
	int	len;

    i = 0;
	while (i < config->map_height)
	{
		config->map[i] = malloc(sizeof(char) * (config->map_width + 1));
		if (!config->map[i])
			return (1);
		len = ft_strlen(map_lines[i]);
		j = 0;
		while (j < len && j < config->map_width)
		{
			config->map[i][j] = map_lines[i][j];
			j++;
		}
		while (j < config->map_width)
		{
			config->map[i][j] = ' ';
			j++;
		}
		config->map[i][config->map_width] = '\0';
		i++;
	}
	config->map[config->map_height] = NULL;
    return (0);
}

int	parse_map(char **map_lines, t_config *config)
{
	if (!map_lines || !map_lines[0])
		return (print_error("Empty map"), 1);
	config->map_height = count_map_lines(map_lines);
	config->map_width = get_max_line_length(map_lines);
	if (config->map_height < 3 || config->map_width < 3)
		return (print_error("Map is too small"), 1);
	config->map = malloc(sizeof(char *) * (config->map_height + 1));
	if (!config->map)
		return (print_error("Memory allocation failed"), 1);
    if (!normalize_map(map_lines, config))
        return (print_error("Memory allocation failed"), 1);
	find_spawn_position(config);
	return (0);
}