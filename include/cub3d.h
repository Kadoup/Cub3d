/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:32:14 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/23 18:27:52 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
#include <stdbool.h>
// # include "../.mlx/mlx.h"
# include "../lib/libft.h"
# include "../minilibx-linux/mlx.h"

# define S_WIDTH 1152
# define S_HEIGHT 864
# define PI 3.14159265358979323846
# define MOVE_SPEED 0.1
#define COLLISION_BUFFER 0.1

enum e_tindex
{
	EAST = 0,
	WEST = 1,
	SOUTH = 2,
	NORTH = 3
};

typedef struct s_img
{
	void	*img;
	int	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	char	dir;
	double	x;
	double	y;
	long	has_moved;
	long	rotate;
	double		angle;
	int		move_x;
	int		move_y;
	double	dir_x;
	double	dir_y;
	
}				t_player;

typedef struct s_singletex
{
	char	*texdir;
	int		size;
}			t_singletex;

typedef struct s_tinfo
{
	int		nb_textures;
	int		size;
	t_singletex no;
	t_singletex we;
	t_singletex ea;
	t_singletex so;
	int		floor_color_hex;
	int		ceiling_color_hex;
	char	*floor_color;
	char	*ceiling_color;
}				t_tinfo;

typedef struct s_ray
{
	double	dir_x;
	int		offset;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_dist_true;
	double	wall_x;
	int		side;
	int		line_height;
}	t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		height;
	int		**textures;
	int		**texture_pixels;
	t_player	player;
	t_tinfo		tinfo;
	t_ray		ray;
}				t_game;

void	init_game(t_game *game, char **argv);
bool	check_edges(t_game *game, int x, int y, char **visited);
void	freemap(t_game *game, char **map);
void	init_texture_pixels(t_game *game);
int		render(t_game *game);
int		update_position(t_game *game);
void	render_game(t_game *game);
void	init_texture_img(t_game *data, t_img *image, t_singletex *texture);
bool	validate_color_components(char *color_str);
void	init_img_clean(t_img *img);
int		check_map(t_game *game);
void	get_player_position(t_game *game);
char	**create_visited_array(t_game *game);
int		convert_colors_to_hex(t_game *game);
int		close_window(t_game *game);
void	free_all_textures(t_game *game, int dofree);
void	free_textures(t_game *game);

#endif
