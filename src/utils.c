/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:03:28 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/01 17:13:08 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}

void	free_split(char **str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	convert(char *color_str)
{
	char	**res;
	int		r;
	int		g;
	int		b;
	int		i;

	i = 0;
	if (color_str[ft_strlen(color_str) - 1] == ',')
		return (1);
	res = ft_split(color_str, ',');
	while (res[i])
		i++;
	if (i != 3)
	{
		free_split(res);
		return (1);
	}
	r = ft_atoi(res[0]);
	g = ft_atoi(res[1]);
	b = ft_atoi(res[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_split(res);
		return (1);
	}
	free_split(res);
	return (rgb_to_hex(r, g, b));
}

int	convert_colors_to_hex(t_game *game)
{
	if (convert(game->tinfo.floor_color) != 1)
		game->tinfo.floor_color_hex = convert(game->tinfo.floor_color);
	else
		return (1);
	if (convert(game->tinfo.ceiling_color) != 1)
		game->tinfo.ceiling_color_hex = convert(game->tinfo.ceiling_color);
	else
		return (1);
	return(0);
}


