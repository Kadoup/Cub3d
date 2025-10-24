/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalmber <emalmber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:05:37 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/24 17:07:56 by emalmber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65361)
	{
		game->player.angle -= 5 * (PI / 180);
		game->player.rotate = 1;
	}
	if (keycode == 65363)
	{
		game->player.angle += 5 * (PI / 180);
		game->player.rotate = 1;
	}
	if (keycode == 119)
		game->player.move_y = 1;
	if (keycode == 115)
		game->player.move_y = -1;
	if (keycode == 97)
		game->player.move_x = -1;
	if (keycode == 100)
		game->player.move_x = 1;
	if (keycode == 65307)
		close_window(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 119)
		game->player.move_y = 0;
	if (key == 115)
		game->player.move_y = 0;
	if (key == 97)
		game->player.move_x = 0;
	if (key == 100)
		game->player.move_x = 0;
	if (key == 65361 || key == 65363)
		game->player.rotate = 0;
	return (0);
}

void	key_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
}
