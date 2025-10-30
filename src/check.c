/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:34:04 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/30 16:32:59 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_edges(t_game *game, int x, int y, char **visited)
{
	if (x < 0 || y < 0 || y >= game->height || x
		>= (int)ft_strlen(game->map[y]))
		return (false);
	if (game->map[y][x] == '1')
		return (true);
	if (visited[y][x] == '1')
		return (true);
	if (game->map[y][x] != '0' && game->map[y][x] != 'N' &&
			game->map[y][x] != 'S' && game->map[y][x] != 'E'
			&& game->map[y][x] != 'W')
		return (false);
	visited[y][x] = '1';
	if (!check_edges(game, x + 1, y, visited))
		return (false);
	if (!check_edges(game, x - 1, y, visited))
		return (false);
	if (!check_edges(game, x, y + 1, visited))
		return (false);
	if (!check_edges(game, x, y - 1, visited))
		return (false);
	return (true);
}

int	check_player_count(t_game *game)
{
	int	player_count;

	player_count = count_players(game);
	if (player_count != 1)
	{
		if (player_count == 0)
			printf("Error\nNo player found in map\n");
		else
			printf("Error\nMore than one player found in map\n");
		return (1);
	}
	return (0);
}

void	clean(t_game *game)
{
	freemap(game, game->map);
	free_all_textures(game, 0);
}

void	check_map_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			if (!is_valid_map_char(game->map[i][j]))
			{
				printf("Error\nInvalid character in map\n");
				clean(game);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

int	check_map(t_game *game)
{
	char	**visited;

	check_map_chars(game);
	if (!check_map_closure(game))
	{
		printf("Error\nInvalid map\n");
		clean(game);
		return (1);
	}
	visited = create_visited_array(game);
	if (check_player_count(game))
	{
		freemap(game, visited);
		clean(game);
		return (1);
	}
	get_player_position(game);
	if (!check_edges(game, game->player.x, game->player.y, visited))
	{
		freemap(game, visited);
		clean(game);
		printf("Error\nInvalid map\n");
		return (1);
	}
	freemap(game, visited);
	return (0);
}
