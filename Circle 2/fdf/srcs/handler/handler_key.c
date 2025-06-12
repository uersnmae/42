/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_key_release.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:05:39 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/02 16:06:53 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "fdf.h"
#include "fdf_hook.h"

void	free_map(t_map *map)
{
	int	i;
	int	j;

	if (map)
	{
		i = 0;
		while (i < map->height)
		{
			j = 0;
			while (j < map->width)
				free(map->grid[i][j++]);
			free(map->grid[i++]);
		}
		free(map->grid);
	}
	free(map);
}

int	exit_program(t_fdf *fdf)
{
	if (fdf->map)
		free_map(fdf->map);
	if (fdf->object)
		free(fdf->object);
	if (fdf->cam)
		free(fdf->cam);
	if (fdf->depth)
		free(fdf->depth);
	if (fdf->img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->mlx_ptr)
		mlx_destroy_display(fdf->mlx_ptr);
	free(fdf->mlx_ptr);
	free(fdf);
	exit(EXIT_SUCCESS);
}

int	key_release_handler(int keycode, t_fdf *fdf)
{
	if (keycode == ESC)
		exit_program(fdf);
	return (0);
}

int	key_press_handler(int keycode, t_fdf *fdf)
{
	if (keycode >= ARROW_LEFT && keycode <= ARROW_DOWN)
		hook_rotate(keycode, fdf);
	if (keycode == KEY_W || keycode == KEY_S || \
		keycode == KEY_A || keycode == KEY_D)
		hook_translate(keycode, fdf);
	if (keycode == KEY_R)
		hook_reset(fdf);
	if (keycode == KEY_T)
		hook_toggle_view(fdf);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	wireframe(fdf->map, fdf);
	return (0);
}
