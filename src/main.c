/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:56:30 by tjourdan          #+#    #+#             */
/*   Updated: 2025/10/27 15:30:27 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**create_visited_array(t_game *game)
{
	char	**visited;
	int		i;
	int		j;

	visited = malloc(sizeof(char *) * game->height);
	i = 0;
	while (i < game->height)
	{
		visited[i] = malloc(sizeof(char) * (ft_strlen(game->map[i]) + 1));
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			visited[i][j] = '0';
			j++;
		}
		visited[i][j] = '\0';
		i++;
	}
	return (visited);
}

static void	set_player_angle(t_game *game)
{
	if (game->player.dir == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->player.dir == 'S')
		game->player.angle = PI / 2;
	else if (game->player.dir == 'E')
		game->player.angle = 0;
	else if (game->player.dir == 'W')
		game->player.angle = PI;
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

static void	init_player(t_game *game, int i, int j)
{
	game->player.x = j + 0.5;
	game->player.y = i + 0.5;
	game->player.dir = game->map[i][j];
	game->map[i][j] = '0';
	set_player_angle(game);
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	get_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			if (is_player_char(game->map[i][j]))
			{
				init_player(game, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}

// void	get_player_position(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < game->height)
// 	{
// 		j = 0;
// 		while (j < (int)ft_strlen(game->map[i]))
// 		{
// 			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
// 				game->map[i][j] == 'E' || game->map[i][j] == 'W')
// 			{
// 				game->player.x = j + 0.5;
// 				game->player.y = i + 0.5;
// 				game->player.dir = game->map[i][j];
// 				game->map[i][j] = '0';
// 				if (game->player.dir == 'N')
// 					game->player.angle = 3 * PI / 2;
// 				else if (game->player.dir == 'S')
// 					game->player.angle = PI / 2;
// 				else if (game->player.dir == 'E')
// 					game->player.angle = 0;
// 				else if (game->player.dir == 'W')
// 					game->player.angle = PI;
// 				game->player.dir_x = cos(game->player.angle);
// 				game->player.dir_y = sin(game->player.angle);
// 				return ;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

int	close_window(t_game *game)
{
	int	i;

	freemap(game, game->map);
	i = 0;
	if (game->texture_pixels)
	{
		while (i < S_HEIGHT)
		{
			if (game->texture_pixels[i])
				free(game->texture_pixels[i]);
			i++;
		}
		free(game->texture_pixels);
	}
	free_all_textures(game, 1);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (1);
	}
	if (ft_strlen(argv[1]) < 4
		|| ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
	{
		printf("Error\nMap file must have .cub extension\n");
		return (1);
	}
	init_game(&game, argv);
	if (check_map(&game))
		return (1);
	init_mlx(&game);
	init_textures(&game);
	key_hooks(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	render_game(&game, true);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
}
