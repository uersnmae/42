/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:53:19 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/27 14:24:59 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "fdf.h"

#define ZOOM_SCALE	1.1

void	scroll_down(t_fdf *fdf)
{
	fdf->object->scale *= ZOOM_SCALE;
}

void	scroll_up(t_fdf *fdf)
{
	fdf->object->scale /= ZOOM_SCALE;
}
