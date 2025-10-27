/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:32:19 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/27 15:32:17 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map_loop(t_game *game, int fd, char **line)
{
	int		i;
	bool	map_started;
	char	*current_line;

	i = 0;
	map_started = false;
	current_line = *line;
	while (current_line != NULL)
	{
		game->i = &i;
		game->map_started = &map_started;
		process_map_line(game, current_line, fd);
		if (map_started && (current_line[0] == '\n' || current_line[0] == '\0'))
		{
			*line = current_line;
			return ;
		}
		free(current_line);
		current_line = gnl(fd);
	}
	*line = current_line;
}

void	readmapfromfile(t_game *game, char *filepath)
{
	int		fd;
	char	*line;

	fd = open(filepath, O_RDONLY);
	skip_textures_and_empty_lines(fd, game, &line);
	read_map_loop(game, fd, &line);
	if (line)
		free(line);
	close(fd);
}

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c
		== 'S' || c == 'E' || c == 'W' || c == ' ');
}

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
	if (i > 0 && (game->map[i - 1][j] == ' '
		|| (j >= (int)ft_strlen(game->map[i - 1]))))
		return (true);
	return (false);
}

bool	has_space_below(t_game *game, int i, int j)
{
	if (i < game->height - 1 && (game->map[i + 1][j] == ' '
		|| (j >= (int)ft_strlen(game->map[i + 1]))))
		return (true);
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

bool	is_cell_enclosed(t_game *game, int i, int j)
{
	if (is_on_edge(game, i, j))
		return (false);
	if (has_space_above(game, i, j))
		return (false);
	if (has_space_below(game, i, j))
		return (false);
	if (has_space_adjacent(game, i, j))
		return (false);
	return (true);
}

bool	check_map_closure(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < (int)ft_strlen(game->map[i]))
		{
			if (is_walkable(game->map[i][j]))
			{
				if (!is_cell_enclosed(game, i, j))
					return (false);
			}
		}
	}
	return (true);
}

// bool	check_map_closure(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < game->height)
// 	{
// 		j = 0;
// 		while (j < (int)ft_strlen(game->map[i]))
// 		{
// 			if (game->map[i][j] == '0' || game->map[i][j] == 'N' ||
// 				game->map[i][j] == 'S' || game->map[i][j] == 'E' ||
// 				game->map[i][j] == 'W')
// 			{
// 				if (i == 0 || i == game->height - 1
// 					|| j == 0 || j == (int)ft_strlen(game->map[i]) - 1)
// 					return (false);
// 				if (i > 0 && (game->map[i - 1][j] == ' '
// 					|| (j >= (int)ft_strlen(game->map[i - 1])
// 						&& game->map[i - 1][j] == '\0')))
// 					return (false);
// 				if (i < game->height - 1 && (game->map[i + 1][j] == ' '
// 					|| (j >= (int)ft_strlen(game->map[i + 1])
// 						&& game->map[i + 1][j] == '\0')))
// 					return (false);
// 				if (j > 0 && game->map[i][j - 1] == ' ')
// 					return (false);
// 				if (j < (int)ft_strlen(game->map[i]) - 1
// 					&& game->map[i][j + 1] == ' ')
// 					return (false);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (true);
// }
