/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:42:58 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/30 16:40:41 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_on_edge(t_game *game, int i, int j)
{
	if (i == 0 || i == game->height - 1)
		return (true);
	if (j == 0 || j == (int)ft_strlen(game->map[i]) - 1)
		return (true);
	return (false);
}

bool	has_space_above(t_game *game, int i, int j)
{
	if (i > 0)
	{
		if (j >= (int)ft_strlen(game->map[i - 1]))
			return (true);
		if (game->map[i - 1][j] == ' ')
			return (true);
	}
	return (false);
}

bool	has_space_below(t_game *game, int i, int j)
{
	if (i < game->height - 1)
	{
		if (j >= (int)ft_strlen(game->map[i + 1]))
			return (true);
		if (game->map[i + 1][j] == ' ')
			return (true);
	}
	return (false);
}

bool	has_space_adjacent(t_game *game, int i, int j)
{
	if (j > 0 && game->map[i][j - 1] == ' ')
		return (true);
	if (j < (int)ft_strlen(game->map[i]) - 1
		&& game->map[i][j + 1] == ' ')
		return (true);
	return (false);
}
