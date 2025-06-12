/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:36:26 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 10:51:34 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "game.h"

#define MOVE_SPEED_PER_SEC	1.5
#define ROT_SPEED_PER_SEC	1.0

void	rotate_player(t_game *game, double rot_direction)
{
	double	rot_val;
	double	old_dir_x;
	double	old_plane_x;

	rot_val = ROT_SPEED_PER_SEC * rot_direction * game->delta_time;
	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	game->dir_x = game->dir_x * cos(rot_val) - game->dir_y * sin(rot_val);
	game->dir_y = old_dir_x * sin(rot_val) + game->dir_y * cos(rot_val);
	game->plane_x = game->plane_x * cos(rot_val)
		- game->plane_y * sin(rot_val);
	game->plane_y = old_plane_x * sin(rot_val)
		+ game->plane_y * cos(rot_val);
}

static void	calculate_movement(t_game *game, double *move_x, double *move_y)
{
	const double	move_step = MOVE_SPEED_PER_SEC * game->delta_time;

	*move_x = 0.0;
	*move_y = 0.0;
	if (game->move_forward)
	{
		*move_x += game->dir_x * move_step;
		*move_y += game->dir_y * move_step;
	}
	if (game->move_backward)
	{
		*move_x -= game->dir_x * move_step;
		*move_y -= game->dir_y * move_step;
	}
	if (game->move_right)
	{
		*move_x += game->plane_x * move_step;
		*move_y += game->plane_y * move_step;
	}
	if (game->move_left)
	{
		*move_x -= game->plane_x * move_step;
		*move_y -= game->plane_y * move_step;
	}
}

static void	apply_movement(t_game *game)
{
	double	move_x;
	double	move_y;

	calculate_movement(game, &move_x, &move_y);
	if (game->map[(int)game->player_y][(int)(game->player_x + move_x)] != '1')
	{
		game->player_x += move_x;
	}
	if (game->map[(int)(game->player_y + move_y)][(int)game->player_x] != '1')
	{
		game->player_y += move_y;
	}
}

void	update_player_state(t_game *game)
{
	if (game->move_forward || game->move_backward
		|| game->move_left || game->move_right)
	{
		apply_movement(game);
	}
	if (game->turn_left)
	{
		rotate_player(game, -1.0);
	}
	if (game->turn_right)
	{
		rotate_player(game, 1.0);
	}
}
