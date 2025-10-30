/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:39:23 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/30 13:39:17 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_players(t_game *game)
{
	int		i;
	size_t	j;
	int		count;

	count = 0;
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < ft_strlen(game->map[i]))
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	set_player_angle(t_game *game)
{
	if (game->player.dir == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->player.dir == 'S')
		game->player.angle = PI / 2;
	else if (game->player.dir == 'E')
		game->player.angle = 0;
	else if (game->player.dir == 'W')
		game->player.angle = PI;
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

void	init_players(t_game *game, int i, int j)
{
	game->player.x = j + 0.5;
	game->player.y = i + 0.5;
	game->player.dir = game->map[i][j];
	game->map[i][j] = '0';
	set_player_angle(game);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	get_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			if (is_player_char(game->map[i][j]))
			{
				init_players(game, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
