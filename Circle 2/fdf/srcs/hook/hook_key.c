/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:28:56 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/02 15:33:01 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_hook.h"

void	hook_translate(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_W)
		fdf->object->offset_y -= 10;
	else if (keycode == KEY_S)
		fdf->object->offset_y += 10;
	else if (keycode == KEY_A)
		fdf->object->offset_x -= 10;
	else if (keycode == KEY_D)
		fdf->object->offset_x += 10;
}

void	hook_reset(t_fdf *fdf)
{
	fdf->object->offset_x = 0;
	fdf->object->offset_y = 0;
	fdf->object->height_z = 1;
	fdf->cam->pos_x = 0.0;
	fdf->cam->pos_y = 0.0;
	fdf->cam->pos_z = 0.0;
	fdf->cam->rot_x = get_radian(120);
	fdf->cam->rot_y = get_radian(30);
	fdf->cam->rot_z = 0.0;
	fdf->cam->toggle = 0;
}

void	hook_toggle_view(t_fdf *fdf)
{
	if (fdf->cam->toggle)
	{
		fdf->object->height_z = 1;
		fdf->cam->pos_x = 0.0;
		fdf->cam->pos_y = 0.0;
		fdf->cam->pos_z = 0.0;
		fdf->cam->rot_x = get_radian(120);
		fdf->cam->rot_y = get_radian(30);
		fdf->cam->rot_z = 0.0;
		fdf->cam->toggle = 0;
	}
	else
	{
		fdf->object->height_z = 1;
		fdf->cam->pos_x = 0.0;
		fdf->cam->pos_y = 0.0;
		fdf->cam->pos_z = 0.0;
		fdf->cam->rot_x = 0.0;
		fdf->cam->rot_y = 0.0;
		fdf->cam->rot_z = 0.0;
		fdf->cam->toggle = 1;
	}
}
