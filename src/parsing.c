/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:11:15 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/09 18:55:41 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_textures(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->no_texture = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->so_texture = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->we_texture = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->ea_texture = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->floor_color = ft_strtrim(line + 2, " \n");
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling_color = ft_strtrim(line + 2, " \n");
	else
		return (0);
	return (1);
}


void	getmapdimensions(t_game *game, char *argv)
{
	char	*line;
	int		fd;

	game->height = 0;
	fd = open(argv, O_RDONLY);
	while (1)
	{
		line = gnl(fd);
		if (line == NULL)
			break ;
		if (get_textures(game, line))
		{
			game->nb_textures++;
			free(line);
			continue ;
		}
		if(line[0] != '\n')
		{
			game->height++;
		}
		free(line);
	}
	close(fd);
}


void	readmapfromfile(t_game *game, char *filepath)
{
	int		fd;
	char	*line;
	int		i;
	
	fd = open(filepath, O_RDONLY);
	i = 0;
	line = gnl(fd);
	while (i < game->nb_textures && line)
	{
		free(line);
		line = gnl(fd);
		i++;
	}
	i = 0;
	while (line != NULL)
	{
		if (line[0] != '\n')
		{
			game->map[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
			ft_strlcpy(game->map[i], line, ft_strlen(line) + 1);
			i++;
		}
		free(line);
		line = gnl(fd);
	}
	free(line);
	close(fd);
}

void	init_game(t_game *game, char **argv)
{
	game->map = NULL;
	game->no_texture = NULL;
	game->so_texture = NULL;
	game->we_texture = NULL;
	game->ea_texture = NULL;
	game->floor_color = NULL;
	game->ceiling_color = NULL;
	game->nb_textures = 0;
	getmapdimensions(game, argv[1]);
	game->map = malloc(sizeof(char *) * game->height);
	readmapfromfile(game, argv[1]);
}