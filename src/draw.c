/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalmber <emalmber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:26:45 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/24 18:29:28 by emalmber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_line(t_game *game, int x)
{
	int		y;
	int		end;
	int		text_index;
	int		line_height;
	int		tex_y;
	double	wall_x;
	int		tex_x;

	y = -game->ray.line_height / 2 + S_HEIGHT / 2;
	end = game->ray.line_height / 2 + S_HEIGHT / 2;
	text_index = get_text_index(game);
	set_size_text(game, text_index);
	while (y < end)
	{
		if (y >= 0 && y < S_HEIGHT)
		{
			line_height = game->ray.line_height;
			tex_y = ((y - (-line_height / 2 + S_HEIGHT / 2))
					* game->tinfo.size) / line_height;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= game->tinfo.size)
				tex_y = game->tinfo.size - 1;
			if (game->ray.side == 0)
				wall_x = game->player.y + game->ray.wall_dist_true
					* game->ray.dir_y;
			else
				wall_x = game->player.x + game->ray.wall_dist_true
					* game->ray.dir_x;
			wall_x -= floor(wall_x);
			tex_x = (int)(wall_x * game->tinfo.size);
			if (game->ray.side == 0 && game->ray.dir_x > 0)
				tex_x = game->tinfo.size - tex_x - 1;
			if (game->ray.side == 1 && game->ray.dir_y < 0)
				tex_x = game->tinfo.size - tex_x - 1;
			if (tex_x < 0)
				tex_x = 0;
			if (tex_x >= game->tinfo.size)
				tex_x = game->tinfo.size - 1;
			game->texture_pixels[y][x]
				= game->textures[text_index][game->tinfo.size * tex_y + tex_x];
		}
		y++;
	}
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
