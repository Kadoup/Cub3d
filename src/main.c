/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:56:30 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/17 15:18:57 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**create_visited_array(t_game *game)
{
	char	**visited;
	int		i, j;
	
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
	return visited;
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
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || 
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				game->player.dir = game->map[i][j];
				game->map[i][j] = '0';
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
				return ;
			}
			j++;
		}
		i++;
	}
}

int	check_map(t_game *game)
{
	char **visited;

	visited = create_visited_array(game);
	get_player_position(game);
	if (!check_edges(game, game->player.x, game->player.y, visited))
	{
		
		freemap(game, visited);
		printf("Error\nMap is not closed\n");
		return (1);
	}
	return (0);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1152, 864, "cub3d");
}

static int	*xpm_to_img(t_game *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(data, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * data->tinfo.size * data->tinfo.size);
	y = 0;
	while (y < data->tinfo.size)
	{
		x = 0;
		while (x < data->tinfo.size)
		{
			buffer[y * data->tinfo.size + x]
				= tmp.addr[y * data->tinfo.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

void	init_textures(t_game *game)
{
	(void)game;
	game->textures = malloc(sizeof(int *) * 4);
	game->textures[NORTH] = xpm_to_img(game, game->tinfo.no);
	game->textures[SOUTH] = xpm_to_img(game, game->tinfo.so);
	game->textures[EAST] = xpm_to_img(game, game->tinfo.ea);
	game->textures[WEST] = xpm_to_img(game, game->tinfo.we);
}

void	init_texture_pixels(t_game *game)
{
	int i;

	game->texture_pixels = ft_calloc((S_HEIGHT), sizeof(int *));
	i = 0;
	while (i < S_HEIGHT)
	{
		game->texture_pixels[i] = ft_calloc((S_WIDTH ), sizeof(int));
		i++;
	}
}

int	key_press(int keycode, t_game *game)
{
	// printf("%f\n", game->player.angle);
	if (keycode == 65361)
	{
		game->player.angle -= 5 * (PI / 180);
		game->player.rotate = 1;
	}
	if (keycode == 65363)
	{
		game->player.angle += 5 * (PI / 180);
		game->player.rotate = 1;
	}
	if (keycode == 119)
		game->player.move_y = 1;
	if (keycode == 115)
		game->player.move_y = -1;
	if (keycode == 97)
		game->player.move_x = -1;
	if (keycode == 100)
		game->player.move_x = 1;
	if (keycode == 65307)
	{
		freemap(game, game->map);
		exit(0);
	}
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 119)
		game->player.move_y = 0;
	if (key == 115)
		game->player.move_y = 0;
	if (key == 97)
		game->player.move_x = 0;
	if (key == 100)
		game->player.move_x = 0;
	return (0);
}

void	key_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
	mlx_hook(game->win, 3, 1L<<1, key_release, game);;
}

int	main(int argc, char **argv)
{
	t_game game;
	// char **visited;
	if (argc != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (1);
	}
	init_game(&game, argv);
	if (check_map(&game))
		return (1);
	init_mlx(&game);
	init_textures(&game);
	key_hooks(&game);
	render_game(&game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	// freemap(&game, visited);
}
