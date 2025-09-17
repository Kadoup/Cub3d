/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:30:11 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/17 16:00:39 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle + PI/2) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle + PI/2) * MOVE_SPEED;
	if (game->map[(int)game->player.y][(int)(new_x)] != '1')
		game->player.x = new_x;
	if (game->map[(int)(new_y)][(int)game->player.x] != '1')
		game->player.y = new_y;
	return (1);
}

int	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle - PI/2) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle - PI/2) * MOVE_SPEED;
	if (game->map[(int)game->player.y][(int)(new_x)] != '1')
		game->player.x = new_x;
	if (game->map[(int)(new_y)][(int)game->player.x] != '1')
		game->player.y = new_y;
	return (1);
}

// int	move_forward(t_game *game)
// {
// 	double	new_x;
// 	double	new_y;
// 	double	buffer = 0.1; // Small buffer to prevent clipping

// 	new_x = game->player.x + cos(game->player.angle) * MOVE_SPEED;
// 	new_y = game->player.y + sin(game->player.angle) * MOVE_SPEED;
	
// 	// Check with buffer
// 	if (game->map[(int)(game->player.y)][(int)(new_x + (new_x > game->player.x ? buffer : -buffer))] != '1')
// 		game->player.x = new_x;
// 	if (game->map[(int)(new_y + (new_y > game->player.y ? buffer : -buffer))][(int)(game->player.x)] != '1')
// 		game->player.y = new_y;
// 	return (1);
// }

int	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle) * MOVE_SPEED;
	if (game->map[(int)game->player.y][(int)(new_x)] != '1')
		game->player.x = new_x;
	if (game->map[(int)(new_y)][(int)game->player.x] != '1')
		game->player.y = new_y;
	return (1);
}

int	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y - sin(game->player.angle) * MOVE_SPEED;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	return (1);
}

int	update_position(t_game *game)
{
	if(game->player.move_x == 1)
		game->player.has_moved += move_right(game);
	if(game->player.move_x == -1)
		game->player.has_moved += move_left(game);
	if(game->player.move_y == 1)
		game->player.has_moved += move_forward(game);
	if(game->player.move_y == -1)
		game->player.has_moved += move_backward(game);
	if(game->player.rotate == 1)
		game->player.has_moved += 1;
	return (game->player.has_moved);
}
