/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:56:30 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/09 18:56:42 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	main(int argc, char **argv)
{
	t_game game;
	if (argc != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (1);
	}
	init_game(&game, argv);
	check_edges(&game);
	for (int i = 0; i < game.height; i++)
	{
		printf("%s\n", game.map[i]);
	}
	printf("%s\n", game.no_texture);
}