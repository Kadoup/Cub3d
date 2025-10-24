/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalmber <emalmber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:06:20 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/24 17:47:41 by emalmber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1152, 864, "cub3d");
}

int	*xpm_to_img(t_game *data, t_singletex *texture)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(data, &tmp, texture);
	buffer = ft_calloc(1,
			sizeof * buffer * texture->size * texture->size);
	y = 0;
	while (y < texture->size)
	{
		x = 0;
		while (x < texture->size)
		{
			buffer[y * texture->size + x]
				= tmp.addr[y * texture->size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

void	free_all_textures(t_game *game, int dofree)
{
	if (dofree)
		free_textures(game);
	free(game->tinfo.no.texdir);
	free(game->tinfo.so.texdir);
	free(game->tinfo.ea.texdir);
	free(game->tinfo.we.texdir);
	free(game->tinfo.ceiling_color);
	free(game->tinfo.floor_color);
}

void	init_textures(t_game *game)
{
	game->textures = ft_calloc(4, sizeof(int *));
	game->textures[NORTH] = xpm_to_img(game, &game->tinfo.no);
	game->textures[SOUTH] = xpm_to_img(game, &game->tinfo.so);
	game->textures[EAST] = xpm_to_img(game, &game->tinfo.ea);
	game->textures[WEST] = xpm_to_img(game, &game->tinfo.we);
}

void	init_texture_pixels(t_game *game)
{
	int	i;

	game->texture_pixels = ft_calloc((S_HEIGHT), sizeof(int *));
	i = 0;
	while (i < S_HEIGHT)
	{
		game->texture_pixels[i] = ft_calloc((S_WIDTH), sizeof(int));
		i++;
	}
}
