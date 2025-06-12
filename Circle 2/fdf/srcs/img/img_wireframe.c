/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_wireframe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:15:44 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/27 14:24:03 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

static int	get_sampling_step(t_fdf *fdf);

void	wireframe(t_map *map, t_fdf *fdf)
{
	int	x;
	int	y;
	int	step;

	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bpp / 8));
	y = 0;
	step = get_sampling_step(fdf);
	while (y + step < map->height && y >= 0)
	{
		x = 0;
		while (x + step < map->width && x >= 0)
		{
			if (x != map->width - 1)
				draw_line_bresenham(fdf, project(fdf, x, y),
					project(fdf, x + step, y));
			if (y != map->height -1)
				draw_line_bresenham(fdf, project(fdf, x, y),
					project(fdf, x, y + step));
			x += step;
		}
		y += step;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}

static int	get_sampling_step(t_fdf *fdf)
{
	long long	total_size;

	total_size = fdf->map->height * fdf->map->width;
	if (total_size > 30000 && fdf->object->scale < 1.0)
		return (8);
	else if (total_size > 30000 && fdf->object->scale < 2.0)
		return (4);
	else if (total_size > 30000)
		return (2);
	else
		return (1);
}
