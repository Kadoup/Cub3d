/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initimg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:16:12 by emalmber          #+#    #+#             */
/*   Updated: 2025/10/30 15:38:58 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
}

void	init_img(t_game *data, t_img *image, int width, int height)
{
	init_img_clean(image);
	image->img = mlx_new_image(data->mlx, width, height);
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}

void	init_ray(t_game *game, float ray_angle)
{
	game->ray.dir_x = cos(ray_angle);
	game->ray.dir_y = sin(ray_angle);
	game->ray.map_x = (int)game->player.x;
	game->ray.map_y = (int)game->player.y;
	game->ray.deltadist_x = fabs(1 / game->ray.dir_x);
	game->ray.deltadist_y = fabs(1 / game->ray.dir_y);
}

void	init_texture_img(t_game *data, t_img *image, t_singletex *texture)
{
	init_img_clean(image);
	image->img = mlx_xpm_file_to_image(data->mlx, texture->texdir,
			&texture->size, &texture->size);
	if (image->img == NULL)
	{
		printf("Error\nFailed to load texture image\n");
		freemap(data, data->map);
		free_all_textures(data, 1);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit (1);
	}
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	return ;
}
