/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalmber <emalmber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:48:32 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/24 18:28:30 by emalmber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_line_height(t_game *game, float ray_angle)
{
	if (game->ray.side == 0)
	{
		game->ray.wall_dist_true = (game->ray.sidedist_x
				- game->ray.deltadist_x);
	}
	else
	{
		game->ray.wall_dist_true = (game->ray.sidedist_y
				- game->ray.deltadist_y);
	}
	game->ray.wall_dist = game->ray.wall_dist_true
		* cos(ray_angle - game->player.angle);
	if (game->ray.wall_dist < 0.001)
		game->ray.wall_dist = 0.001;
	game->ray.line_height = (int)(S_HEIGHT / game->ray.wall_dist);
}

int	get_text_index(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (game->ray.dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
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
	int		half_width;
	float	seglen;

	i = 0;
	half_width = S_WIDTH / 2;
	seglen = tan((80 * (PI / 180)) / S_WIDTH);
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
