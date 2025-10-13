/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:34:04 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/13 15:33:43 by tjourdan         ###   ########.fr       */
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
