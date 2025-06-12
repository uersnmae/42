/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:02:04 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/01 14:06:06 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	matrix_identity(void)
{
	t_matrix	mat;
	t_mat_index	i;
	t_mat_index	j;

	i = 0;
	while (i < ROW)
	{
		j = 0;
		while (j < COL)
		{
			if (i == j)
				mat.m[i][j] = 1.0;
			else
				mat.m[i][j] = 0.0;
			++j;
		}
		++i;
	}
	return (mat);
}

t_matrix	matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix	result;
	t_mat_index	i;
	t_mat_index	j;
	t_mat_index	k;

	result = matrix_identity();
	i = 0;
	while (i < ROW)
	{
		j = 0;
		while (j < COL)
		{
			result.m[i][j] = 0.0;
			k = -1;
			while (++k < COL)
				result.m[i][j] += a.m[i][k] * b.m[k][j];
			++j;
		}
		++i;
	}
	return (result);
}

t_matrix	matrix_translation(double tx, double ty, double tz)
{
	t_matrix	mat;

	mat = matrix_identity();
	mat.m[0][3] = tx;
	mat.m[1][3] = ty;
	mat.m[2][3] = tz;
	return (mat);
}

t_matrix	matrix_scaling(double sx, double sy, double sz)
{
	t_matrix	mat;

	mat = matrix_identity();
	mat.m[0][0] = sx;
	mat.m[1][1] = sy;
	mat.m[2][2] = sz;
	return (mat);
}
