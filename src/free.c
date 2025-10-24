/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalmber <emalmber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:23:00 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/24 18:24:07 by emalmber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	freemap(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_textures(t_game *game)
{
	if (game->textures)
	{
		if (game->textures[NORTH])
			free(game->textures[NORTH]);
		if (game->textures[SOUTH])
			free(game->textures[SOUTH]);
		if (game->textures[EAST])
			free(game->textures[EAST]);
		if (game->textures[WEST])
			free(game->textures[WEST]);
		free(game->textures);
	}
}
