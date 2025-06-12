/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:50:51 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 18:19:17 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <stdlib.h>

#include "mlx.h"
#include "game.h"
#include "parser.h"

void	free_game_tex(t_game *game)
{
	void	*mlx_ptr;
	int		i;

	if (!game->tex)
		return ;
	mlx_ptr = game->mlx_wrap->mlx_ptr;
	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->tex[i].img)
			mlx_destroy_image(mlx_ptr, game->tex[i].img);
		i++;
	}
	free(game->tex);
	game->tex = NULL;
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->z_buffer)
		free(game->z_buffer);
	if (game->tex)
		free_game_tex(game);
	if (game->mlx_wrap)
	{
		if (game->mlx_wrap->img_ptr)
			mlx_destroy_image(game->mlx_wrap->mlx_ptr, game->mlx_wrap->img_ptr);
		if (game->mlx_wrap->win_ptr)
			mlx_destroy_window(game->mlx_wrap->mlx_ptr,
				game->mlx_wrap->win_ptr);
		if (game->mlx_wrap->mlx_ptr)
			mlx_destroy_display(game->mlx_wrap->mlx_ptr);
		free(game->mlx_wrap->mlx_ptr);
		free(game->mlx_wrap);
	}
	if (game->cfg)
	{
		free_cfg(game->cfg);
	}
	free(game);
}

int	exit_game(t_game *game)
{
	free_game(game);
	exit(0);
}
