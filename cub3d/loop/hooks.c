/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:57:21 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 10:50:05 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <stdio.h>

#include "game.h"
#include "mlx.h"
#include "loop.h"

#define MOUSE_SENSITIVITY	0.007

static int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		game->should_exit = true;
	if (keycode == KEY_W)
		game->move_forward = true;
	else if (keycode == KEY_S)
		game->move_backward = true;
	if (keycode == KEY_A)
		game->move_left = true;
	else if (keycode == KEY_D)
		game->move_right = true;
	if (keycode == KEY_LEFT)
		game->turn_left = true;
	else if (keycode == KEY_RIGHT)
		game->turn_right = true;
	printf("%d\n", keycode);
	return (0);
}

static int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		game->should_exit = false;
	if (keycode == KEY_W)
		game->move_forward = false;
	else if (keycode == KEY_S)
		game->move_backward = false;
	if (keycode == KEY_A)
		game->move_left = false;
	else if (keycode == KEY_D)
		game->move_right = false;
	if (keycode == KEY_LEFT)
		game->turn_left = false;
	else if (keycode == KEY_RIGHT)
		game->turn_right = false;
	return (0);
}

static int	mouse_move_handler(int x, int y, t_game *game)
{
	int	delta_x;

	(void)y;
	if (game->mouse_x == -1)
	{
		game->mouse_x = x;
		return (0);
	}
	delta_x = x - game->mouse_x;
	if (delta_x != 0)
		rotate_player(game, delta_x * MOUSE_SENSITIVITY);
	mlx_mouse_move(game->mlx_wrap->mlx_ptr, game->mlx_wrap->win_ptr,
		game->screen_w / 2, game->screen_h / 2);
	game->mouse_x = game->screen_w / 2;
	return (0);
}

void	init_hooks(t_game *game)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = game->mlx_wrap->mlx_ptr;
	win_ptr = game->mlx_wrap->win_ptr;
	mlx_hook(win_ptr, KeyPress, ShiftMask, key_press_handler, game);
	mlx_hook(win_ptr, KeyRelease, LockMask, key_release_handler, game);
	mlx_hook(win_ptr, DestroyNotify, 0, exit_game, game);
	mlx_hook(win_ptr, MotionNotify, PointerMotionMask,
		mouse_move_handler, game);
	mlx_mouse_hide(mlx_ptr, win_ptr);
	game->mouse_x = -1;
}
