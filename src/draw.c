/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:26:45 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/30 13:37:16 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_game *game, int x, int y, int text_index)
{
	int		tex_y;
	int		tex_x;
	double	wall_x;

	tex_y = calculate_tex_y(game, y);
	wall_x = calculate_wall_x(game);
	tex_x = calculate_tex_x(game, wall_x);
	game->texture_pixels[y][x]
		= game->textures[text_index][game->tinfo.size * tex_y + tex_x];
}

void	draw_wall_line(t_game *game, int x)
{
	int	y;
	int	end;
	int	text_index;

	y = -game->ray.line_height / 2 + S_HEIGHT / 2;
	end = game->ray.line_height / 2 + S_HEIGHT / 2;
	text_index = get_text_index(game);
	set_size_text(game, text_index);
	while (y < end)
	{
		if (y >= 0 && y < S_HEIGHT)
			draw_pixel(game, x, y, text_index);
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
