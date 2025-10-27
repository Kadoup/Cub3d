/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:30:15 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/27 15:18:25 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_textures_and_empty_lines(int fd, t_game *game, char **line)
{
	int	i;

	i = 0;
	*line = gnl(fd);
	while (i < game->tinfo.nb_textures && *line)
	{
		if (ft_strncmp(*line, "NO ", 3) == 0 || ft_strncmp(*line, "SO ", 3) == 0
			|| ft_strncmp(*line, "WE ", 3) == 0 || ft_strncmp(*line, "EA ", 3)
			== 0 || ft_strncmp(*line, "F ", 2) == 0
			|| ft_strncmp(*line, "C ", 2) == 0)
			i++;
		free(*line);
		*line = gnl(fd);
	}
	while (*line && ((*line)[0] == '\n' || (*line)[0] == '\0'))
	{
		free(*line);
		*line = gnl(fd);
	}
}

bool	check_empty_lines_in_map(int fd)
{
	char	*next_line;
	bool	has_more_content;

	has_more_content = false;
	next_line = gnl(fd);
	while (next_line != NULL)
	{
		if (next_line[0] != '\n' && next_line[0] != '\0')
		{
			has_more_content = true;
			free(next_line);
			break ;
		}
		free(next_line);
		next_line = gnl(fd);
	}
	return (has_more_content);
}

void	handle_map_line(t_game *game, char *line, int *i, bool *map_started)
{
	if (line[0] != '\n' && line[0] != '\0')
	{
		if (*map_started == false)
			*map_started = true;
		game->map[*i] = malloc(sizeof(char) * (ft_strlen(line)));
		ft_strlcpy(game->map[*i], line, ft_strlen(line));
		(*i)++;
	}
}

void	handle_empty_line_in_map(char *line, int fd, t_game *game)
{
	char	*tmp;

	free(line);
	tmp = gnl(fd);
	while (tmp != NULL)
	{
		free(tmp);
		tmp = gnl(fd);
	}
	close(fd);
	cleanup_game(game);
	printf("Error\nEmpty lines not allowed within map\n");
	exit(0);
}

void	process_map_line(t_game *game, char *line, int fd)
{
	if (line[0] != '\n' && line[0] != '\0')
		handle_map_line(game, line, game->i, game->map_started);
	else if (game->map_started && check_empty_lines_in_map(fd))
		handle_empty_line_in_map(line, fd, game);
	else if (game->map_started)
		return ;
}
