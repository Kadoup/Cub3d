/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:48:32 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/13 18:10:48 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	init_ray(t_game *game, float ray_angle)
{
	game->ray.dir_x = cos(ray_angle);
	game->ray.dir_y = sin(ray_angle);
	game->ray.map_x = (int)game->player.x;
	game->ray.map_y = (int)game->player.y;
	game->ray.deltadist_x = fabs(1 / game->ray.dir_x);
	game->ray.deltadist_y = fabs(1 / game->ray.dir_y);
}

void	prep_dda(t_game *game)
{
	if (game->ray.dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.sidedist_x = (game->player.x - game->ray.map_x)
			* game->ray.deltadist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.sidedist_x = (game->ray.map_x + 1.0 - game->player.x)
			* game->ray.deltadist_x;
	}
	if (game->ray.dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.sidedist_y = (game->player.y - game->ray.map_y)
			* game->ray.deltadist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.sidedist_y = (game->ray.map_y + 1.0 - game->player.y)
			* game->ray.deltadist_y;
	}
}

void	process_dda(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->ray.sidedist_x < game->ray.sidedist_y)
		{
			game->ray.sidedist_x += game->ray.deltadist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sidedist_y += game->ray.deltadist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->map[game->ray.map_y][game->ray.map_x] != '0')
			hit = 1;
	}
}

void	calc_line_height(t_game *game, float ray_angle)
{
	if (game->ray.side == 0)
	{
		game->ray.wall_dist_true = (game->ray.sidedist_x - game->ray.deltadist_x);
	}
	else
	{
		game->ray.wall_dist_true = (game->ray.sidedist_y - game->ray.deltadist_y);
	}
	game->ray.wall_dist = game->ray.wall_dist_true * cos(ray_angle - game->player.angle);
	if (game->ray.wall_dist < 0.001)
		game->ray.wall_dist = 0.001;	
	game->ray.line_height = (int)(S_HEIGHT / game->ray.wall_dist);
}

int	get_text_index(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.dir_x > 0)
			return EAST;
		else
			return WEST;
	}
	else
	{
		if (game->ray.dir_y > 0)
			return SOUTH;
		else
			return NORTH;
	}
}

void	init_texture_img(t_game *data, t_img *image, t_singletex *texture)
{
	init_img_clean(image);
	image->img = mlx_xpm_file_to_image(data->mlx, texture->texdir, &texture->size,
			&texture->size);
	if (image->img == NULL)
		exit(1);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}


void	set_size_text(t_game *game, int text_index)
{
	if (text_index == NORTH)
		game->tinfo.size = game->tinfo.no.size;
	if (text_index == SOUTH)
		game->tinfo.size = game->tinfo.so.size;
	if (text_index == EAST)
		game->tinfo.size = game->tinfo.ea.size;
	if (text_index == WEST)
		game->tinfo.size = game->tinfo.we.size;
}

void	draw_wall_line(t_game *game, int x)
{
	int	y;
	int end;
	int	text_index;

	y = -game->ray.line_height / 2 + S_HEIGHT / 2;
	end = game->ray.line_height / 2 + S_HEIGHT / 2;
	text_index = get_text_index(game);
	set_size_text(game, text_index);
	while (y < end)
	{
		if (y >= 0 && y < S_HEIGHT)
		{
			int line_height = game->ray.line_height;
			int tex_y = ((y - (-line_height / 2 + S_HEIGHT / 2)) * game->tinfo.size) / line_height;
			if (tex_y < 0) tex_y = 0;
			if (tex_y >= game->tinfo.size) tex_y = game->tinfo.size - 1;
			double wall_x;
			if (game->ray.side == 0)
				wall_x = game->player.y + game->ray.wall_dist_true * game->ray.dir_y;
			else
				wall_x = game->player.x + game->ray.wall_dist_true * game->ray.dir_x;
			wall_x -= floor(wall_x);

			int tex_x = (int)(wall_x * game->tinfo.size);
			if (game->ray.side == 0 && game->ray.dir_x > 0)
				tex_x = game->tinfo.size - tex_x - 1;
			if (game->ray.side == 1 && game->ray.dir_y < 0)
				tex_x = game->tinfo.size - tex_x - 1;

			if (tex_x < 0) tex_x = 0;
			if (tex_x >= game->tinfo.size) tex_x = game->tinfo.size - 1;

			game->texture_pixels[y][x] = game->textures[text_index][game->tinfo.size * tex_y + tex_x];
		}
		y++;
	}
}

void	cast_single_ray(t_game *game, int x, float ray_angle)
{
	prep_dda(game);
	process_dda(game);
	calc_line_height(game, ray_angle);
	draw_wall_line(game, x);
}

void	cast_rays(t_game *game)
{
	int		i;
	float	ray_angle;

	i = 0;
	int half_width = S_WIDTH / 2;
	float seglen = tan((80 * (PI / 180)) / S_WIDTH);
	game->ray.offset = 0;
	while (i < S_WIDTH)
	{
		ray_angle = game->player.angle + atan((i - half_width) * seglen);
		while (ray_angle < 0)
			ray_angle += 2 * PI;
		while (ray_angle >= 2 * PI)
			ray_angle -= 2 * PI;
		init_ray(game, ray_angle);
		cast_single_ray(game, i, ray_angle);
		i++;
	}
}

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
}

void	init_img(t_game *data, t_img *image, int width, int height)
{
	init_img_clean(image);
	image->img = mlx_new_image(data->mlx, width, height);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->line_length / 4) + x;
	image->addr[pixel] = color;
}

void	set_frame_image_pixel(t_game *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < S_HEIGHT / 2)
		set_image_pixel(image, x, y, data->tinfo.ceiling_color_hex);
	else if (y < S_HEIGHT - 1)
		set_image_pixel(image, x, y, data->tinfo.floor_color_hex);
}

void	render_frame(t_game *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, S_WIDTH, S_HEIGHT);
	y = 0;
	while (y < S_HEIGHT)
	{
		x = 0;
		while (x < S_WIDTH)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

void	render_game(t_game *game)
{
	init_texture_pixels(game);
	cast_rays(game);
	render_frame(game);
}

int	render(t_game *game)
{
	game->player.has_moved = update_position(game);
	if (!game->player.has_moved)
		return (0);
	render_game(game);
	game->player.has_moved = 0;
	return (0);
}
