/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:53:27 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/02 15:28:38 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_hook.h"

int	hook_rotate(int keycode, t_fdf *fdf)
{
	if (keycode == ARROW_UP)
		fdf->cam->rot_y += get_radian(10);
	if (keycode == ARROW_DOWN)
		fdf->cam->rot_y -= get_radian(10);
	if (keycode == ARROW_LEFT)
		fdf->cam->rot_x += get_radian(10);
	if (keycode == ARROW_RIGHT)
		fdf->cam->rot_x -= get_radian(10);
	return (0);
}
