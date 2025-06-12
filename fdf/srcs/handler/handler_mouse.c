/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:03:52 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/27 13:35:30 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <X11/Xutil.h>
#include "mlx.h"
#include "fdf.h"
#include "fdf_hook.h"

int	mouse_handler(int keycode, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (keycode == Button4)
		scroll_down(fdf);
	if (keycode == Button5)
		scroll_up(fdf);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	wireframe(fdf->map, fdf);
	return (0);
}
