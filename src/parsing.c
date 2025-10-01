/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:11:15 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/01 16:31:08 by tjourdan         ###   ########.fr       */
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
	bool	map_started;
	
	fd = open(filepath, O_RDONLY);
	i = 0;
	map_started = false;
	line = gnl(fd);
	
	// Skip texture/color lines
	while (i < game->tinfo.nb_textures && line)
	{
		free(line);
		line = gnl(fd);
		i++;
	}
	
	// Skip empty lines before map starts
	while (line && (line[0] == '\n' || line[0] == '\0'))
	{
		free(line);
		line = gnl(fd);
	}
	
	i = 0;
	while (line != NULL)
	{
		if (line[0] != '\n' && line[0] != '\0')
		{
			map_started = true;
			game->map[i] = malloc(sizeof(char) * (ft_strlen(line)));
			ft_strlcpy(game->map[i], line, ft_strlen(line));
			i++;
		}
		else if (map_started)
		{
			// Empty line found after map started - this is an error
			free(line);
			close(fd);
			printf("Error\nEmpty lines not allowed within map\n");
			exit(0);
		}
		free(line);
		line = gnl(fd);
	}
	free(line);
	close(fd);
}


// void	readmapfromfile(t_game *game, char *filepath)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;
	
// 	fd = open(filepath, O_RDONLY);
// 	i = 0;
// 	line = gnl(fd);
// 	while (i < game->tinfo.nb_textures && line)
// 	{
// 		free(line);
// 		line = gnl(fd);
// 		i++;
// 	}
// 	i = 0;
// 	while (line != NULL)
// 	{
// 		if (line[0] != '\n')
// 		{
// 			game->map[i] = malloc(sizeof(char) * (ft_strlen(line)));
// 			ft_strlcpy(game->map[i], line, ft_strlen(line));
// 			i++;
// 		}
// 		free(line);
// 		line = gnl(fd);
// 	}
// 	free(line);
// 	close(fd);
// }

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

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool	check_map_closure(t_game *game)
{
	int	i, j;
	
	// Check each cell in the map
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			// If we find a walkable space (0, N, S, E, W)
			if (game->map[i][j] == '0' || game->map[i][j] == 'N' || 
				game->map[i][j] == 'S' || game->map[i][j] == 'E' || 
				game->map[i][j] == 'W')
			{
				// Check if it's on the border
				if (i == 0 || i == game->height - 1 || 
					j == 0 || j == (int)ft_strlen(game->map[i]) - 1)
					return (false);
				
				// Check all 4 directions for walls or valid chars
				if (i > 0 && (game->map[i-1][j] == ' ' || 
					(j >= (int)ft_strlen(game->map[i-1]) && game->map[i-1][j] == '\0')))
					return (false);
				if (i < game->height - 1 && (game->map[i+1][j] == ' ' || 
					(j >= (int)ft_strlen(game->map[i+1]) && game->map[i+1][j] == '\0')))
					return (false);
				if (j > 0 && game->map[i][j-1] == ' ')
					return (false);
				if (j < (int)ft_strlen(game->map[i]) - 1 && game->map[i][j+1] == ' ')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	check_map(t_game *game)
{
	char **visited;

	// First check if map is properly closed
	if (!check_map_closure(game))
	{
		printf("Error\nMap is not properly closed\n");
		return (1);
	}

	visited = create_visited_array(game);
	get_player_position(game);
	
	// Then check reachability from player position
	if (!check_edges(game, game->player.x, game->player.y, visited))
	{
		freemap(game, visited);
		printf("Error\nMap is not closed\n");
		return (1);
	}
	
	freemap(game, visited);
	return (0);
}

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
	game->map = malloc(sizeof(char *) * game->height);
	readmapfromfile(game, argv[1]);
	if (convert_colors_to_hex(game))
		exit(1);
}
