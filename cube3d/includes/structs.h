// includes/structs.h
#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
	int		spawn_x;
	int		spawn_y;
	char	spawn_dir;
}	t_config;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_config	config;
}	t_game;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

#endif