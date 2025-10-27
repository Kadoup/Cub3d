/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:11:15 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/27 15:47:14 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_textures(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->tinfo.no.texdir = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->tinfo.so.texdir = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->tinfo.we.texdir = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->tinfo.ea.texdir = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->tinfo.floor_color = ft_strtrim(line + 2, " \n");
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->tinfo.ceiling_color = ft_strtrim(line + 2, " \n");
	else
		return (0);
	return (1);
}

bool	process_line(t_game *game, char *line)
{
	if (get_textures(game, line))
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
