/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:03:29 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/05 15:29:11 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int	i;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * fdf->bpp / 8) + (y * fdf->size_line);
		fdf->data_addr[i] = color & 0xFF;
		fdf->data_addr[i + 1] = (color >> 8);
		fdf->data_addr[i + 2] = (color >> 16);
		fdf->data_addr[i + 3] = (color >> 24);
	}
}

void	img_put_pixel_with_depth(t_fdf *fdf, t_pixel pixel)
{
	int	i;
	int	index;

	if (pixel.x >= 0 && pixel.x < WIDTH && pixel.y >= 0 && pixel.y < HEIGHT)
	{
		index = pixel.x + pixel.y * WIDTH;
		if (pixel.z < fdf->depth[index])
		{
			i = (pixel.x * fdf->bpp / 8) + (pixel.y * fdf->size_line);
			fdf->data_addr[i] = pixel.color & 0xFF;
			fdf->data_addr[i + 1] = (pixel.color >> 8);
			fdf->data_addr[i + 2] = (pixel.color >> 16);
			fdf->data_addr[i + 3] = (pixel.color >> 24);
		}
	}
}
