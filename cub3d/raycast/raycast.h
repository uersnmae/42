/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:47:22 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 10:47:59 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "game.h"

typedef struct s_ctl
{
	t_tex			*tex;
	int				tex_idx;
	double			wall_x;
	double			step;
	double			tex_pos;
	double			pos_y;
	double			pos_x;
	int				tex_x;
	int				y;
	unsigned int	color;
}	t_ctl;

typedef struct s_raycast
{
	char	**map;
	t_game	*game;
	t_ctl	tex_ctl;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	pos_x;
	double	pos_y;
	int		x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		screen_w;
	int		screen_h;
}	t_raycast;

void	run_raycast(t_game *game);
void	cal_step_and_init_side_dist(t_raycast *ray);
void	set_ray(t_raycast *ray, int x);
void	run_dda_until_hit(t_raycast *ray);
void	cal_wall_height(t_raycast *ray);
void	draw_texture(t_raycast *ray);

#endif
