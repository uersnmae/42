/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_put_bresenham_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:14:23 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/06 11:40:39 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "fdf.h"

#define X		0
#define Y		1
#define TOTAL	0
#define CURRENT	1

static void	draw_line_bresenham_loop(t_fdf *fdf, t_point p[2],
				int d[2], int s[2]);
static void	draw_line_bresenham_loop_helper(t_point p[2], int *err,
				int d[2], int s[2]);
static int	get_color(unsigned c1, unsigned c2, double t);
static int	final_color(int start, int end, double t);

void	draw_line_bresenham(t_fdf *fdf, t_point start, t_point end)
{
	t_point	points[2];
	int		d[2];
	int		s[2];

	d[0] = (int)ft_abs(end.x - start.x);
	d[1] = (int)ft_abs(end.y - start.y);
	s[0] = -1;
	if (start.x < end.x)
		s[0] = 1;
	s[1] = -1;
	if (start.y < end.y)
		s[1] = 1;
	points[0] = start;
	points[1] = end;
	draw_line_bresenham_loop(fdf, points, d, s);
}

static void	draw_line_bresenham_loop(t_fdf *fdf, t_point p[2],
				int d[2], int s[2])
{
	int		err;
	double	dist[2];
	t_point	p_start;
	double	t;
	t_pixel	pixel;

	err = d[X] - d[Y];
	p_start = p[X];
	dist[0] = sqrt(pow(p[1].x - p_start.x, 2) + pow(p[1].y - p_start.y, 2));
	if (dist[0] == 0)
		dist[0] = 1;
	while (1)
	{
		dist[1] = sqrt(pow(p[0].x - p_start.x, 2) + pow(p[0].y - p_start.y, 2));
		t = dist[1] / dist[0];
		pixel.x = p[0].x;
		pixel.y = p[0].y;
		pixel.z = (int)round(p[0].z * (1 - t) + p[1].z * t);
		pixel.color = get_color(p_start.color, p[1].color, t);
		img_put_pixel_with_depth(fdf, pixel);
		if (p[0].x == p[1].x && p[0].y == p[1].y)
			break ;
		draw_line_bresenham_loop_helper(p, &err, d, s);
	}
}

static void	draw_line_bresenham_loop_helper(t_point p[2], int *err,
										int d[2], int s[2])
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 > -d[Y])
	{
		*err -= d[Y];
		p->x += s[X];
	}
	if (e2 < d[X])
	{
		*err += d[X];
		p->y += s[Y];
	}
}

static int	get_color(unsigned c1, unsigned c2, double percent)
{
	int	a;
	int	r;
	int	g;
	int	b;
	int	ret;

	a = final_color((c1 >> 24) & 0xFF, (c2 >> 24) & 0xFF, percent);
	r = final_color((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, percent);
	g = final_color((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, percent);
	b = final_color((c1) & 0xFF, (c2) & 0xFF, percent);
	ret = ((r << 16) | (g << 8) | b);
	if (ret == 0x000000)
		return (c2);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

static int	final_color(int start, int end, double t)
{
	return ((int)((1 - t) * start + t * end));
}
