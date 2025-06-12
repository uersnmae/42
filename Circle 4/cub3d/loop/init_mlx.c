/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:44:52 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/08 12:51:01 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

#include "mlx.h"
#include "libft.h"
#include "game.h"
#include "utils.h"

int	init_mlx(t_game *game)
{
	game->mlx_wrap = ft_calloc(1, sizeof(t_mlx));
	if (!game->mlx_wrap)
		return (-1);
	game->mlx_wrap->mlx_ptr = mlx_init();
	if (!game->mlx_wrap->mlx_ptr)
		return (error_status(0, 0, "Error: mlx_init() failed"));
	game->mlx_wrap->win_ptr = mlx_new_window(game->mlx_wrap->mlx_ptr,
			game->screen_w, game->screen_h, "cub3D");
	if (!game->mlx_wrap->win_ptr)
		return (error_status(0, 0, "Error: mlx_new_window() failed"));
	game->mlx_wrap->img_ptr = mlx_new_image(game->mlx_wrap->mlx_ptr,
			game->screen_w, game->screen_h);
	if (!game->mlx_wrap->img_ptr)
		return (error_status(0, 0, "Error: mlx_new_image() failed"));
	game->mlx_wrap->data_addr = mlx_get_data_addr(game->mlx_wrap->img_ptr,
			&game->mlx_wrap->bpp, &game->mlx_wrap->line_len,
			&game->mlx_wrap->endian);
	return (0);
}
