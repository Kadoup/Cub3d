/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalmber <emalmber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:34:32 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/24 18:16:19 by emalmber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_singletex(t_singletex *infos)
{
	infos->size = 0;
	infos->texdir = NULL;
}

void	init_tinfo(t_tinfo *tinfo)
{
	tinfo->nb_textures = 0;
	init_singletex(&tinfo->no);
	init_singletex(&tinfo->so);
	init_singletex(&tinfo->we);
	init_singletex(&tinfo->ea);
	tinfo->floor_color = NULL;
	tinfo->ceiling_color = NULL;
}

void	init_game(t_game *game, char **argv)
{
	int	i;

	i = 0;
	game->map = NULL;
	init_tinfo(&game->tinfo);
	game->player.x = -1;
	game->player.y = -1;
	game->player.angle = 0;
	game->player.move_x = 0;
	game->player.move_y = 0;
	game->player.rotate = 0;
	game->player.has_moved = 0;
	getmapdimensions(game, argv[1]);
	if (validate_textures_and_colors(game))
	{
		cleanup_game(game);
		exit(1);
	}
	game->map = malloc(sizeof(char *) * game->height);
	while (i < game->height)
	{
		game->map[i] = NULL;
		i++;
	}
	readmapfromfile(game, argv[1]);
	if (convert_colors_to_hex(game))
		exit(1);
}
