/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:03:28 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/30 13:38:23 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_rgb_components(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

int	validate_rgb_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	return (0);
}

int	convert(char *color_str)
{
	char	**res;
	int		rgb[3];

	if (color_str[ft_strlen(color_str) - 1] == ',')
		return (1);
	res = ft_split(color_str, ',');
	if (count_rgb_components(res) != 3)
	{
		free_split(res);
		return (1);
	}
	rgb[0] = ft_atoi(res[0]);
	rgb[1] = ft_atoi(res[1]);
	rgb[2] = ft_atoi(res[2]);
	if (validate_rgb_range(rgb[0], rgb[1], rgb[2]))
	{
		free_split(res);
		return (1);
	}
	free_split(res);
	return (rgb_to_hex(rgb[0], rgb[1], rgb[2]));
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
	return (0);
}

int	open_map_file(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCannot open file\n");
		exit(1);
	}
	return (fd);
}
