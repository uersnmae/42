/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:15:47 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/01 14:57:59 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "matrix.h"

static void		homogeneous_coord(double orig_x, double orig_y,
					double orig_z, double vec[4]);
static t_matrix	get_final_matrix(t_fdf *fdf);
static void		get_result(t_matrix final, double res[4], double vec[4]);

t_point	project(t_fdf *fdf, int grid_x, int grid_y)
{
	t_point		p;
	double		vec[4];
	double		res[4];
	t_matrix	final;

	homogeneous_coord(grid_x, grid_y, fdf->map->grid[grid_y][grid_x][0], vec);
	final = get_final_matrix(fdf);
	get_result(final, res, vec);
	p.x = (int)round((res[0] + 1) * (WIDTH / 2.0)) + fdf->object->offset_x;
	p.y = (int)round((1 - res[1]) * (HEIGHT / 2.0)) + fdf->object->offset_y;
	p.z = (int)round(res[2]);
	if (fdf->map->grid[grid_y][grid_x][1] == -1)
		p.color = 0x00FFFFFF;
	else
		p.color = fdf->map->grid[grid_y][grid_x][1];
	p.reverse = 0;
	return (p);
}

static void	get_result(t_matrix final, double res[4], double vec[4])
{
	t_mat_index	i;
	t_mat_index	j;

	i = 0;
	while (i < ROW)
	{
		res[i] = 0.0;
		j = 0;
		while (j < COL)
		{
			res[i] += final.m[i][j] * vec[j];
			++j;
		}
		++i;
	}
}

static void	homogeneous_coord(double orig_x, double orig_y,
				double orig_z, double vec[4])
{
	vec[0] = orig_x;
	vec[1] = orig_y;
	vec[2] = orig_z;
	vec[3] = 1;
}

static t_matrix	get_final_matrix(t_fdf *fdf)
{
	t_matrix	model;
	t_matrix	view;
	t_matrix	proj;
	t_matrix	final;
	t_ortho		ortho;

	model = compute_model_matrix(fdf->map, fdf->object);
	view = compute_view_matrix(fdf->cam);
	init_ortho(&ortho);
	proj = create_ortho_projection(&ortho);
	final = matrix_multiply(proj, matrix_multiply(view, model));
	return (final);
}
