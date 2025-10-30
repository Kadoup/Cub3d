/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:11:15 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/30 15:28:21 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_textures(t_game *game, char *line)
{
	if (check_duplicate(game, line))
		return (-1);
	if (parse_texture(game, line))
		return (1);
	if (parse_color(game, line))
		return (1);
	return (0);
}

bool	process_line(t_game *game, char *line)
{
	int	result;

	result = get_textures(game, line);
	if (result == -1)
	{
		return (printf("Error\nDuplicate identifier found\n"), false);
	}
	if (result == 1)
	{
		game->tinfo.nb_textures++;
		return (true);
	}
	if (line[0] != '\n')
		game->height++;
	return (false);
}

void	getmapdimensions(t_game *game, char *argv)
{
	char	*line;
	int		fd;

	game->height = 0;
	fd = open_map_file(argv);
	while (1)
	{
		line = gnl(fd);
		if (line == NULL)
			break ;
		process_line(game, line);
		free(line);
	}
	close(fd);
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	free(game->tinfo.no.texdir);
	free(game->tinfo.so.texdir);
	free(game->tinfo.we.texdir);
	free(game->tinfo.ea.texdir);
	free(game->tinfo.floor_color);
	free(game->tinfo.ceiling_color);
	if (game->map)
	{
		i = 0;
		while (game->map[i])
			free(game->map[i++]);
		free(game->map);
	}
}

int	validate_textures_and_colors(t_game *game)
{
	if (!game->tinfo.no.texdir)
		return (printf("Error\nMissing NO texture\n"), 1);
	if (!game->tinfo.so.texdir)
		return (printf("Error\nMissing SO texture\n"), 1);
	if (!game->tinfo.we.texdir)
		return (printf("Error\nMissing WE texture\n"), 1);
	if (!game->tinfo.ea.texdir)
		return (printf("Error\nMissing EA texture\n"), 1);
	if (!game->tinfo.floor_color)
		return (printf("Error\nMissing floor color (F)\n"), 1);
	if (!game->tinfo.ceiling_color)
		return (printf("Error\nMissing ceiling color (C)\n"), 1);
	if (!validate_color_components(game->tinfo.floor_color))
		return (printf("Error\nInvalid floor color (must be 0-255)\n"), 1);
	if (!validate_color_components(game->tinfo.ceiling_color))
		return (printf("Error\nInvalid ceiling color (must be 0-255)\n"), 1);
	return (0);
}
