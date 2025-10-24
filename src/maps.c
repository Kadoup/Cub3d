/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalmber <emalmber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:32:19 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/24 17:46:48 by emalmber         ###   ########.fr       */
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
		process_map_line(game, current_line, &i, &map_started, fd);
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

bool	check_map_closure(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			if (game->map[i][j] == '0' || game->map[i][j] == 'N' ||
				game->map[i][j] == 'S' || game->map[i][j] == 'E' ||
				game->map[i][j] == 'W')
			{
				if (i == 0 || i == game->height - 1
					|| j == 0 || j == (int)ft_strlen(game->map[i]) - 1)
					return (false);
				if (i > 0 && (game->map[i - 1][j] == ' '
					|| (j >= (int)ft_strlen(game->map[i - 1])
						&& game->map[i - 1][j] == '\0')))
					return (false);
				if (i < game->height - 1 && (game->map[i + 1][j] == ' '
					|| (j >= (int)ft_strlen(game->map[i + 1])
						&& game->map[i + 1][j] == '\0')))
					return (false);
				if (j > 0 && game->map[i][j - 1] == ' ')
					return (false);
				if (j < (int)ft_strlen(game->map[i]) - 1
					&& game->map[i][j + 1] == ' ')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
