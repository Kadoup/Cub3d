/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:03:28 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/23 18:27:46 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}

bool	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

bool	validate_color_components(char *color_str)
{
	char	**rgb_split;
	int		r, g, b;
	int		i;
	bool	valid;

	rgb_split = ft_split(color_str, ',');
	if (!rgb_split || !rgb_split[0] || !rgb_split[1] || !rgb_split[2] || rgb_split[3])
	{
		if (rgb_split)
		{
			i = 0;
			while (rgb_split[i])
				free(rgb_split[i++]);
			free(rgb_split);
		}
		return (false);
	}
	r = ft_atoi(rgb_split[0]);
	g = ft_atoi(rgb_split[1]);
	b = ft_atoi(rgb_split[2]);
	valid = validate_rgb_value(r) && validate_rgb_value(g) && validate_rgb_value(b);
	i = 0;
	while (rgb_split[i])
		free(rgb_split[i++]);
	free(rgb_split);
	return (valid);
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


