/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:44:58 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 10:44:59 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_background(t_game *g)
{
	int				y;
	int				x;
	unsigned int	*row;
	unsigned int	col;

	y = 0;
	while (y < g->screen_h)
	{
		row = (unsigned int *)(g->mlx_wrap->data_addr
				+ y * g->mlx_wrap->line_len);
		if (y < g->screen_h / 2)
			col = g->ceil_color;
		else
			col = g->floor_color;
		x = 0;
		while (x < g->screen_w)
		{
			row[x] = col;
			x++;
		}
		y++;
	}
}
