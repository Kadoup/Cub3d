/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:23:36 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/30 15:24:19 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_duplicate(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && game->tinfo.no.texdir)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0 && game->tinfo.so.texdir)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0 && game->tinfo.we.texdir)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0 && game->tinfo.ea.texdir)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0 && game->tinfo.floor_color)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0 && game->tinfo.ceiling_color)
		return (1);
	return (0);
}

int	parse_texture(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->tinfo.no.texdir = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->tinfo.so.texdir = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->tinfo.we.texdir = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->tinfo.ea.texdir = ft_strtrim(line + 3, " \n");
	else
		return (0);
	return (1);
}

int	parse_color(t_game *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		game->tinfo.floor_color = ft_strtrim(line + 2, " \n");
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->tinfo.ceiling_color = ft_strtrim(line + 2, " \n");
	else
		return (0);
	return (1);
}
