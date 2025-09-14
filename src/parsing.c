/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:11:15 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/14 04:16:41 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_textures(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->tinfo.no = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->tinfo.so = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->tinfo.we = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->tinfo.ea = ft_strtrim(line + 3, " \n");
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->tinfo.floor_color = ft_strtrim(line + 2, " \n");
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->tinfo.ceiling_color = ft_strtrim(line + 2, " \n");
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
			game->tinfo.nb_textures++;
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
	while (i < game->tinfo.nb_textures && line)
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
			game->map[i] = malloc(sizeof(char) * (ft_strlen(line)));
			ft_strlcpy(game->map[i], line, ft_strlen(line));
			i++;
		}
		free(line);
		line = gnl(fd);
	}
	free(line);
	close(fd);
}

bool	check_edges(t_game *game, int x, int y, char **visited)
{
	if (x < 0 || y < 0 || y >= game->height || x >= (int)ft_strlen(game->map[y]))
		return false;
	if (game->map[y][x] == '1')
		return true;
	if (visited[y][x] == '1')
		return true;
	if (game->map[y][x] != '0' && game->map[y][x] != 'N' && 
			game->map[y][x] != 'S' && game->map[y][x] != 'E' && game->map[y][x] != 'W')
		return false;
	visited[y][x] = '1';
	if (!check_edges(game, x + 1, y, visited))
		return false;
	if (!check_edges(game, x - 1, y, visited))
		return false;
	if (!check_edges(game, x, y + 1, visited))
		return false;
	if (!check_edges(game, x, y - 1, visited))
		return false;
	return true;
}

void	init_tinfo(t_tinfo *tinfo)
{
	tinfo->nb_textures = 0;
	tinfo->no = NULL;
	tinfo->so = NULL;
	tinfo->we = NULL;
	tinfo->ea = NULL;
	tinfo->floor_color = NULL;
	tinfo->ceiling_color = NULL;
}

void	init_game(t_game *game, char **argv)
{
	game->map = NULL;
	init_tinfo(&game->tinfo);
	game->player.x = -1;
	game->player.y = -1;
	game->player.angle = 0;
	game->player.move_x = 0;
	game->player.move_y = 0;
	getmapdimensions(game, argv[1]);
	game->map = malloc(sizeof(char *) * game->height);
	readmapfromfile(game, argv[1]);
}
