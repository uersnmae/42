/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:09:41 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 18:19:33 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "parser.h"
#include "game.h"
#include "mlx.h"
#include "loop.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_config	*cfg;
	t_game		*game;

	if (argc != 2)
		error_status(EXIT_FAILURE, 0, "Usage: ./cub3D <map_file.cub>");
	cfg = ft_calloc(1, sizeof(t_config));
	if (parse_config(argv[1], cfg))
	{
		error_status(EXIT_FAILURE, 0, "Error: Failed to parse map config");
	}
	game = init_game_context(cfg);
	if (!game)
	{
		error_status(EXIT_FAILURE, 0, "Error: Failed to initialize game");
	}
	init_hooks(game);
	mlx_loop_hook(game->mlx_wrap->mlx_ptr, main_loop, game);
	mlx_loop(game->mlx_wrap->mlx_ptr);
	exit_game(game);
	return (0);
}
