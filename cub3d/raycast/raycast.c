/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:17:35 by hakslee           #+#    #+#             */
/*   Updated: 2025/06/09 11:49:36 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "raycast.h"
#include <math.h>

void	game_to_raycast(t_game *game, t_raycast *ray)
{
	ray->game = game;
	ray->pos_x = game->player_x;
	ray->pos_y = game->player_y;
	ray->dir_x = game->dir_x;
	ray->dir_y = game->dir_y;
	ray->plane_x = game->plane_x;
	ray->plane_y = game->plane_y;
	ray->screen_w = game->screen_w;
	ray->screen_h = game->screen_h;
	ray->map = game->map;
}

void	pixel_put(t_raycast *ray, int y, unsigned int color)
{
	char	*dst;
	t_mlx	*mlx;

	mlx = ray->game->mlx_wrap;
	dst = mlx->data_addr + (y * mlx->line_len + ray->x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	get_tex_and_wall_x(t_raycast *ray, t_ctl *tex_ctl)
{
	if (ray->side == 0)
	{
		tex_ctl->wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
		if (ray->step_x > 0)
			tex_ctl->tex_idx = TEX_EAST;
		else
			tex_ctl->tex_idx = TEX_WEST;
	}
	else
	{
		tex_ctl->wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
		if (ray->step_y > 0)
			tex_ctl->tex_idx = TEX_SOUTH;
		else
			tex_ctl->tex_idx = TEX_NORTH;
	}
	tex_ctl->wall_x -= floor(tex_ctl->wall_x);
	tex_ctl->tex = &ray->game->tex[tex_ctl->tex_idx];
}

void	draw_texture(t_raycast *ray)
{
	t_ctl			tex_ctl;
	int				y;
	unsigned int	color;

	get_tex_and_wall_x(ray, &tex_ctl);
	tex_ctl.tex_x = (int)(tex_ctl.wall_x * (double)tex_ctl.tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || \
		(ray->side == 1 && ray->ray_dir_y > 0))
		tex_ctl.tex_x = tex_ctl.tex->width - tex_ctl.tex_x - 1;
	tex_ctl.step = 1.0 * tex_ctl.tex->height / ray->line_height;
	tex_ctl.tex_pos = (ray->draw_start - ray->screen_h / 2.0 \
		+ ray->line_height / 2.0) * tex_ctl.step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_ctl.y = (int)tex_ctl.tex_pos % tex_ctl.tex->height;
		tex_ctl.tex_pos += tex_ctl.step;
		color = *(unsigned int *)(tex_ctl.tex->data_addr + \
			(tex_ctl.y * tex_ctl.tex->line_len + tex_ctl.tex_x * \
			(tex_ctl.tex->bpp / 8)));
		pixel_put(ray, y, color);
		y++;
	}
}

void	run_raycast(t_game *game)
{
	t_raycast	ray;
	int			i;

	i = 0;
	game_to_raycast(game, &ray);
	while (i < ray.screen_w)
	{
		ray.x = i;
		set_ray(&ray, i);
		run_dda_until_hit(&ray);
		cal_wall_height(&ray);
		draw_texture(&ray);
		i++;
	}
}
