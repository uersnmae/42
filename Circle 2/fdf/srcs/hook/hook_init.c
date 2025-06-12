/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:09:21 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/27 13:06:46 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "mlx.h"
#include "fdf.h"

void	init_hook(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, DestroyNotify,
		NoEventMask, exit_program, fdf);
	mlx_hook(fdf->win_ptr, KeyRelease,
		KeyReleaseMask, key_release_handler, fdf);
	mlx_hook(fdf->win_ptr, KeyPress,
		KeyPressMask, key_press_handler, fdf);
	mlx_mouse_hook(fdf->win_ptr, mouse_handler, fdf);
}
