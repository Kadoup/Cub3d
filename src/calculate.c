/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:15:02 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/31 15:52:07 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calculate_tex_y(t_game *game, int y)
{
	int	line_height;
	int	tex_y;

	line_height = game->ray.line_height;
	tex_y = ((y - (-line_height / 2 + S_HEIGHT / 2))
			* game->tinfo.size) / line_height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= game->tinfo.size)
		tex_y = game->tinfo.size - 1;
	return (tex_y);
}

double	calculate_wall_x(t_game *game)
{
	double	wall_x;

	if (game->ray.side == 0)
		wall_x = game->player.y + game->ray.wall_dist_true * game->ray.dir_y;
	else
		wall_x = game->player.x + game->ray.wall_dist_true * game->ray.dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	calculate_tex_x(t_game *game, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * game->tinfo.size);
	if (game->ray.side == 0 && game->ray.dir_x > 0)
		tex_x = game->tinfo.size - tex_x - 1;
	if (game->ray.side == 1 && game->ray.dir_y < 0)
		tex_x = game->tinfo.size - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= game->tinfo.size)
		tex_x = game->tinfo.size - 1;
	return (tex_x);
}

int	cleaner(t_game *game, char **visited)
{
	freemap(game, visited);
	clean(game);
	return (1);
}
