// srcs/parsing/parse_config.c
#include "cube3d.h"

int	parse_texture(char *line, char **texture_path, char *identifier)
{
	char	*trimmed;
	char	*path_start;
	
	trimmed = trim_whitespace(line);	
	if (ft_strncmp(trimmed, identifier, ft_strlen(identifier)) != 0)
		return (1);
	path_start = trimmed + ft_strlen(identifier);
	while (*path_start == ' ' || *path_start == '\t')
		path_start++;
	if (*path_start == '\0')
	{
		print_error("Missing texture path");
		return (1);
	}
	*texture_path = strdup(path_start);
	if (!*texture_path)
	{
		print_error("Memory allocation failed");
		return (1);
	}
	return (0);
}

int	parse_color(char *line, t_color *color, char identifier)
{
	char	*trimmed;
	char	*color_start;
	int		r, g, b;
	
	trimmed = trim_whitespace(line);
	if (trimmed[0] != identifier)
		return (1);
	color_start = trimmed + 1;
	while (*color_start == ' ' || *color_start == '\t')
		color_start++;
	if (sscanf(color_start, "%d,%d,%d", &r, &g, &b) != 3)
	{
		print_error("Invalid color format");
		return (1);
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		print_error("Color values must be between 0 and 255");
		return (1);
	}
	color->r = r;
	color->g = g;
	color->b = b;
	return (0);
}

int	parse_element(char *line, t_config *config)
{
	char	*trimmed;
	
	trimmed = trim_whitespace(line);
	
	if (strlen(trimmed) == 0)
		return (0);  // Ligne vide, ignore
	
	if (ft_strncmp(trimmed, "NO", 2) == 0)
		return (parse_texture(line, &config->north_texture, "NO"));
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		return (parse_texture(line, &config->south_texture, "SO"));
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		return (parse_texture(line, &config->west_texture, "WE"));
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		return (parse_texture(line, &config->east_texture, "EA"));	
	else if (trimmed[0] == 'F')
		return (parse_color(line, &config->floor_color, 'F'));
	else if (trimmed[0] == 'C')
		return (parse_color(line, &config->ceiling_color, 'C'));
	else if (trimmed[0] == '1' || trimmed[0] == '0' || trimmed[0] == ' ')
		return (2);
	print_error("Unknown element in config file");
	return (1);
}

int	parse_config_file(const char *filename, t_config *config)
{
	int		fd;
	char	*line;
	char	**map_lines;
	int		map_count = 0;
	int		map_capacity = 100;
	int		result;
	int		i;
	
	if (ft_strlen(filename) < 4 || ft_strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
		return (print_error("Map file must have .cub extension"), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open file"), 1);
	map_lines = malloc(sizeof(char *) * map_capacity);
	if (!map_lines)
		return (close(fd), 1);
	while ((line = get_next_line(fd)) != NULL)
	{
		result = parse_element(line, config);
		if (result == 1)
		{
			free(line);
			close(fd);
			i = 0;
            while (i < map_count)
            {
				free(map_lines[i]);
                i++;
            }
			free(map_lines);
			return (1);
		}
		else if (result == 2)
		{
			map_lines[map_count] = ft_strdup(line);
			map_count++;
			free(line);
			while ((line = get_next_line(fd)) != NULL)
			{
				if (map_count >= map_capacity - 1)
				{
					map_capacity *= 2;
					map_lines = ft_realloc(map_lines, sizeof(char *) * map_capacity);
				}
				map_lines[map_count] = ft_strdup(line);
				map_count++;
				free(line);
			}
			break;
		}
		free(line);
	}
	close(fd);
	map_lines[map_count] = NULL;
	if (parse_map(map_lines, config) != 0)
	{
		i = 0;
        while (i < map_count)
        {
			free(map_lines[i]);
            i++;
        }
		free(map_lines);
		return (1);
	}
	i = 0;
    while (i < map_count) // faire fonction free_map
    {
		free(map_lines[i]);
        i++;
    }
	free(map_lines);
	return (0);
}