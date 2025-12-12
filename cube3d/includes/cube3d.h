// includes/cube3d.h
#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include "structs.h"

// Constantes
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

// Fonctions de parsing
int		parse_config_file(const char *filename, t_config *config);
int		parse_map(char **lines, t_config *config);
int		parse_element(char *line, t_config *config);
int		parse_texture(char *line, char **texture_path, char *identifier);
int		parse_color(char *line, t_color *color, char identifier);
int		validate_map(t_config *config);
char	*trim_whitespace(char *str);
int		is_valid_map_char(char c);
char	*get_next_line(int fd);

// Fonctions utilitaires
void	free_config(t_config *config);
void	print_error(const char *message);

#endif