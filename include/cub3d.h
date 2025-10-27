/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:32:14 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/27 15:25:59 by tjourdan         ###   ########.fr       */
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
# include <stdbool.h>
# include "../lib/libft.h"
# include "../minilibx-linux/mlx.h"

# define S_WIDTH 1152
# define S_HEIGHT 864
# define PI 3.14159265358979323846
# define MOVE_SPEED 0.1
# define COLLISION_BUFFER 0.1

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
	int		*addr;
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
	double	angle;
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
	int			nb_textures;
	int			size;
	t_singletex	no;
	t_singletex	we;
	t_singletex	ea;
	t_singletex	so;
	int			floor_color_hex;
	int			ceiling_color_hex;
	char		*floor_color;
	char		*ceiling_color;
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
	void		*mlx;
	void		*win;
	char		**map;
	int			height;
	int			**textures;
	int			**texture_pixels;
	t_player	player;
	t_tinfo		tinfo;
	t_ray		ray;
	int		*i;
	bool	*map_started;
}				t_game;

/* ************************************************************************** */
/*                                MAIN.C                                      */
/* ************************************************************************** */
char	**create_visited_array(t_game *game);
void	get_player_position(t_game *game);
int		close_window(t_game *game);

/* ************************************************************************** */
/*                                INIT.C                                      */
/* ************************************************************************** */
void	init_game(t_game *game, char **argv);
void	init_singletex(t_singletex *infos);
void	init_tinfo(t_tinfo *tinfo);

/* ************************************************************************** */
/*                                KEY.C                                       */
/* ************************************************************************** */
int		key_press(int keycode, t_game *game);
int		key_release(int key, t_game *game);
void	key_hooks(t_game *game);

/* ************************************************************************** */
/*                                MOVE.C                                      */
/* ************************************************************************** */
int		move_left(t_game *game);
int		move_right(t_game *game);
int		move_forward(t_game *game);
int		move_backward(t_game *game);
int		update_position(t_game *game);

/* ************************************************************************** */
/*                                RAYCASTING.C                                */
/* ************************************************************************** */
void	calc_line_height(t_game *game, float ray_angle);
int		get_text_index(t_game *game);
void	set_size_text(t_game *game, int text_index);
void	cast_single_ray(t_game *game, int x, float ray_angle);
void	cast_rays(t_game *game);

/* ************************************************************************** */
/*                                DDA.C                                       */
/* ************************************************************************** */
void	prep_dda(t_game *game);
void	process_dda(t_game *game);

/* ************************************************************************** */
/*                                DRAW.C                                      */
/* ************************************************************************** */
void	draw_wall_line(t_game *game, int x);
void	set_image_pixel(t_img *image, int x, int y, int color);
void	set_frame_image_pixel(t_game *data, t_img *image, int x, int y);

/* ************************************************************************** */
/*                                RENDER.C                                    */
/* ************************************************************************** */
void	render_frame(t_game *data);
void	render_game(t_game *game, bool first);
int		render(t_game *game);

/* ************************************************************************** */
/*                                TEXTURE.C                                   */
/* ************************************************************************** */
void	init_mlx(t_game *game);
void	init_textures(t_game *game);
int		*xpm_to_img(t_game *data, t_singletex *texture);
void	free_all_textures(t_game *game, int dofree);
void	init_texture_pixels(t_game *game, bool first);

/* ************************************************************************** */
/*                                UTILS.C                                     */
/* ************************************************************************** */
int		convert(char *color_str);
int		convert_colors_to_hex(t_game *game);

/* ************************************************************************** */
/*                                PARSING.C                                   */
/* ************************************************************************** */
int		get_textures(t_game *game, char *line);
void	getmapdimensions(t_game *game, char *argv);
void	cleanup_game(t_game *game);
int		count_players(t_game *game);
int		validate_textures_and_colors(t_game *game);

/* ************************************************************************** */
/*                                MAPS.C                                      */
/* ************************************************************************** */
void	readmapfromfile(t_game *game, char *filepath);
void	read_map_loop(t_game *game, int fd, char **line);
bool	is_valid_map_char(char c);
bool	check_map_closure(t_game *game);

/* ************************************************************************** */
/*                                CHECK.C                                     */
/* ************************************************************************** */
int		check_map(t_game *game);
int		check_player_count(t_game *game);
bool	check_edges(t_game *game, int x, int y, char **visited);

/* ************************************************************************** */
/*                                LINES.C                                     */
/* ************************************************************************** */
void	skip_textures_and_empty_lines(int fd, t_game *game, char **line);
bool	check_empty_lines_in_map(int fd);
void	handle_map_line(t_game *game, char *line, int *i, bool *map_started);
void	handle_empty_line_in_map(char *line, int fd, t_game *game);
void	process_map_line(t_game *game, char *line, int fd);

/* ************************************************************************** */
/*                                INITIMG.C                                   */
/* ************************************************************************** */
void	init_img_clean(t_img *img);
void	init_img(t_game *data, t_img *image, int width, int height);
void	init_texture_img(t_game *data, t_img *image, t_singletex *texture);
void	init_ray(t_game *game, float ray_angle);

/* ************************************************************************** */
/*                                FREE.C                                      */
/* ************************************************************************** */
void	free_split(char **str);
void	freemap(t_game *game, char **map);
void	free_textures(t_game *game);
void	free_texture_pixels(t_game *game);
void	free_rgb_split(char **rgb_split);

/* ************************************************************************** */
/*                                CALCULATE.C                                 */
/* ************************************************************************** */
int	calculate_tex_y(t_game *game, int y);
double	calculate_wall_x(t_game *game);
int	calculate_tex_x(t_game *game, double wall_x);

/* ************************************************************************** */
/*                                RGB.C                                       */
/* ************************************************************************** */
int		rgb_to_hex(int r, int g, int b);
bool	validate_rgb_value(int value);
bool	is_valid_rgb_format(char **rgb_split);
bool	check_rgb_values(char **rgb_split);
bool	validate_color_components(char *color_str);

#endif
