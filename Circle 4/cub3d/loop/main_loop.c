/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:07:47 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 10:49:35 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>

#include "game.h"
#include "loop.h"
#include "mlx.h"
#include "raycast.h"

int	main_loop(t_game *game)
{
	static struct timeval	last_time;
	struct timeval			current_time;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0)
		last_time = current_time;
	game->delta_time = (current_time.tv_sec - last_time.tv_sec)
		+ (current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	last_time = current_time;
	if (game->should_exit)
	{
		mlx_loop_end(game->mlx_wrap->mlx_ptr);
		return (0);
	}
	update_player_state(game);
	draw_background(game);
	run_raycast(game);
	mlx_put_image_to_window(game->mlx_wrap->mlx_ptr,
		game->mlx_wrap->win_ptr,
		game->mlx_wrap->img_ptr, 0, 0);
	limit_frame_sleep(&current_time);
	return (0);
}
