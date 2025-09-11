/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:34:04 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/10 18:12:48 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freemap(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_error(char *mess, t_game *game, int free)
{
	ft_putstr_fd(mess, 2);
	if (free == 1)
		freemap(game, game->map);
	exit (1);
}

// void	check_edges(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (i < game->height)
// 	{
// 		if (i == 0 || i == game->height - 1)
// 		{
// 			j = 0;
// 			while (game->map[i][j])
// 			{
// 				if (game->map[i][j] != '1' && game->map[i][j] != ' ')
// 					ft_error("Error\nMap must be closed\n", game, 1);
// 				j++;
// 			}
// 		}
// 		else
// 		{
// 			if (game->map[i][0] != '1' || game->map[i][ft_strlen(game->map[i]) - 1] != '1')
// 			{
// 				ft_error("Error\nMap must be closed\n", game, 1);
// 			}
// 		}
// 		i++;
// 	}
// }