/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:32:14 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/09 18:51:20 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
// # include "../.mlx/mlx.h"
# include "../lib/libft.h"

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char	**mapcpy;
	int		height;
	int		nb_textures;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*floor_color;
	char	*ceiling_color;
}				t_game;

void	init_game(t_game *game, char **argv);
void	check_edges(t_game *game);

#endif