/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:08:36 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/29 12:20:55 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H

# define SO_LONG_H
# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# include "../lib/ft_printf/include/ft_printf.h"
# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"

# ifdef __APPLE__

# define KEY_ESC     53
# define KEY_W       13
# define KEY_A       0
# define KEY_S       1
# define KEY_D       2
# define KEY_LEFT    123
# define KEY_RIGHT   124
# define KEY_DOWN    125
# define KEY_UP      126

# else

#define KEY_ESC     65307
#define KEY_W       119
#define KEY_A       97
#define KEY_S       115
#define KEY_D       100
#define KEY_LEFT    65361
#define KEY_RIGHT   65363
#define KEY_DOWN    65364
#define KEY_UP      65362
#endif

typedef struct s_map
{
	char	**grid;
	bool	**visited;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		collect_found;
}	t_map;

typedef struct	s_game
{
	void	*mlx;
	void	*player;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*floor;
	void	*window;
	t_map	*map;
	int		img_size;
	int		moves;
	int		collected;
}	t_game;

// ====================GET_NEXT_LINE====================
char			*get_next_line(int fd);
size_t			ft_strlen_gnl(const char *s);
char			*ft_strchr_gnl(const char *s, int c);
char			*ft_strjoin_gnl(char *s1, char *s2);
char			*ft_strdup_gnl(const char *s);
char			*ft_substr_gnl(char const *s, unsigned int start, size_t len);

// ====================MAIN.C====================
int				main(int ac, char **av);
int				init_game(t_game *game, t_map *map);
int				handle_key(int keycode, t_game *game);
int				check_map(t_map *map, char *filename);

// ====================check_and_init_map.c====================
int				parse_map(t_map *map, char *filename);
int				check_file_extension(char *filename);
t_map			*init_map(void);
int				stock_map_in_grid(t_map *map, char *filename);
int				check_width(t_map *map, char *line, int current_width);

// ====================MAP_ELEMENTS_VERIFICATION.C====================
int				check_walls_validity(t_map *map);
int				check_c(t_map *map);
int				check_ep(t_map *map);
int				set_exit(t_map *map, int y, int x);
int				set_player(t_map *map, int y, int x);

// ====================MAP_CHECK_PLAYABLE.C====================
int				check_map_playable(t_map *map);
bool			flood_fill(t_map *map, int x, int y);
int				init_visited_map(t_map *map);

// ====================INIT_GAME.C====================
void			draw_map(t_game *game);
void			*put_sprites(void *mlx, char *path);
int				load_sprites(t_game *game);

// ====================HANDLE_KEY.C====================
int				close_window(t_game *game);
void			display_moves(t_game *game);
int				check_next_position(t_game *game, int next_y, int next_x);
void			move_player(t_game *game, int new_y, int new_x);

// ====================FREE.C====================
void			free_map(t_map *map);
void			free_map_visited(t_map *map);
void			free_sprites(t_game *game);

#endif
