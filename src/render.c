/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalmber <emalmber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:20:03 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/24 18:20:40 by emalmber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
