/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:22:53 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/27 15:23:14 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

bool	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

bool	is_valid_rgb_format(char **rgb_split)
{
	if (!rgb_split || !rgb_split[0] || !rgb_split[1]
		|| !rgb_split[2] || rgb_split[3])
		return (false);
	return (true);
}

bool	check_rgb_values(char **rgb_split)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(rgb_split[0]);
	g = ft_atoi(rgb_split[1]);
	b = ft_atoi(rgb_split[2]);
	return (validate_rgb_value(r) && validate_rgb_value(g)
		&& validate_rgb_value(b));
}

bool	validate_color_components(char *color_str)
{
	char	**rgb_split;
	bool	valid;

	rgb_split = ft_split(color_str, ',');
	if (!is_valid_rgb_format(rgb_split))
	{
		free_rgb_split(rgb_split);
		return (false);
	}
	valid = check_rgb_values(rgb_split);
	free_rgb_split(rgb_split);
	return (valid);
}
