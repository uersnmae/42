/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:17:35 by hakslee           #+#    #+#             */
/*   Updated: 2025/06/09 10:48:57 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

void	cal_step_and_init_side_dist(t_raycast *raycast)
{
	double	side_x;
	double	side_y;

	if (raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		side_x = (raycast->pos_x - raycast->map_x) * raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		side_x = (raycast->map_x + 1 - raycast->pos_x) * raycast->delta_dist_x;
	}
	if (raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		side_y = (raycast->pos_y - raycast->map_y) * raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		side_y = (raycast->map_y + 1 - raycast->pos_y) * raycast->delta_dist_y;
	}
	raycast->side_dist_x = side_x;
	raycast->side_dist_y = side_y;
}

void	set_ray(t_raycast *raycast, int x)
{
	raycast->camera_x = 2.0 * x / raycast->screen_w - 1;
	raycast->ray_dir_x = raycast->dir_x + raycast->plane_x * raycast->camera_x;
	raycast->ray_dir_y = raycast->dir_y + raycast->plane_y * raycast->camera_x;
	raycast->map_x = (int)raycast->pos_x;
	raycast->map_y = (int)raycast->pos_y;
	if (raycast->ray_dir_x == 0)
		raycast->delta_dist_x = 1e30;
	else
		raycast->delta_dist_x = \
			sqrt(1 + (raycast->ray_dir_y * raycast->ray_dir_y)
				/ (raycast->ray_dir_x * raycast->ray_dir_x));
	if (raycast->ray_dir_y == 0)
		raycast->delta_dist_y = 1e30;
	else
		raycast->delta_dist_y = \
			sqrt(1 + (raycast->ray_dir_x * raycast->ray_dir_x)
				/ (raycast->ray_dir_y * raycast->ray_dir_y));
	raycast->hit = 0;
	cal_step_and_init_side_dist(raycast);
}

void	run_dda_until_hit(t_raycast *raycast)
{
	while (raycast->hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (raycast->map[raycast->map_y][raycast->map_x] == '1')
			raycast->hit = 1;
	}
}

void	cal_wall_height(t_raycast *raycast)
{
	if (raycast->side == 0)
		raycast->perp_wall_dist = (raycast->map_x - raycast->pos_x + \
				(1 - raycast->step_x) / 2.0) / raycast->ray_dir_x;
	else
		raycast->perp_wall_dist = (raycast->map_y - raycast->pos_y + \
				(1 - raycast->step_y) / 2.0) / raycast->ray_dir_y;
	raycast->line_height = (int)(raycast->screen_h / raycast->perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + raycast->screen_h / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + raycast->screen_h / 2;
	if (raycast->draw_end >= raycast->screen_h)
		raycast->draw_end = raycast->screen_h - 1;
}
