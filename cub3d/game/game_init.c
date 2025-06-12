/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:59:18 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 16:12:16 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "libft.h"

static unsigned int	rgb_to_u32(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	copy_map_from_config(t_game *game)
{
	game->map = game->cfg->map;
	game->map_rows = game->cfg->map_height;
	game->map_cols = game->cfg->map_width;
}

void	init_player_direction(t_game *game)
{
	const char	dir_char = game->cfg->player_dir;

	game->player_x = game->cfg->player_x;
	game->player_y = game->cfg->player_y;
	if (dir_char == 'N' || dir_char == 'S')
	{
		game->dir_x = 0.0;
		game->dir_y = -1.0 + (2.0 * (dir_char == 'S'));
		game->plane_x = 0.66 - (1.32 * (dir_char == 'S'));
		game->plane_y = 0.0;
	}
	if (dir_char == 'W' || dir_char == 'E')
	{
		game->dir_x = -1.0 + (2.0 * (dir_char == 'E'));
		game->dir_y = 0.0;
		game->plane_x = 0.0;
		game->plane_y = -0.66 + (1.32 * (dir_char == 'E'));
	}
}

static void	init_game_state(t_game *game, t_config *cfg)
{
	game->cfg = cfg;
	game->screen_w = SCREEN_WIDTH;
	game->screen_h = SCREEN_HEIGHT;
	game->move_forward = false;
	game->move_backward = false;
	game->move_left = false;
	game->move_right = false;
	game->turn_left = false;
	game->turn_right = false;
	game->tex = NULL;
	game->z_buffer = NULL;
	game->floor_color = rgb_to_u32(cfg->floor_rgb);
	game->ceil_color = rgb_to_u32(cfg->ceil_rgb);
}

t_game	*init_game_context(t_config *cfg)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	init_game_state(game, cfg);
	copy_map_from_config(game);
	init_player_direction(game);
	if (init_mlx(game) != 0)
	{
		free_game(game);
		return (NULL);
	}
	if (load_all_textures(game) != 0)
	{
		free_game(game);
		return (NULL);
	}
	return (game);
}
