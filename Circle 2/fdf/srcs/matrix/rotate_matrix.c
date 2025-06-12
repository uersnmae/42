/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:27:34 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/01 13:36:35 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "matrix.h"

t_matrix	matrix_x_rotate(double radian)
{
	t_matrix	mat;
	double		cos_a;
	double		sin_a;

	mat = matrix_identity();
	cos_a = cos(radian);
	sin_a = sin(radian);
	mat.m[1][1] = cos_a;
	mat.m[1][2] = -sin_a;
	mat.m[2][1] = sin_a;
	mat.m[2][2] = cos_a;
	return (mat);
}

t_matrix	matrix_y_rotate(double radian)
{
	t_matrix	mat;
	double		cos_b;
	double		sin_b;

	mat = matrix_identity();
	cos_b = cos(radian);
	sin_b = sin(radian);
	mat.m[0][0] = cos_b;
	mat.m[0][2] = sin_b;
	mat.m[2][0] = -sin_b;
	mat.m[2][2] = cos_b;
	return (mat);
}

t_matrix	matrix_z_rotate(double radian)
{
	t_matrix	mat;
	double		cos_r;
	double		sin_r;

	mat = matrix_identity();
	cos_r = cos(radian);
	sin_r = sin(radian);
	mat.m[0][0] = cos_r;
	mat.m[0][1] = -sin_r;
	mat.m[1][0] = sin_r;
	mat.m[1][1] = cos_r;
	return (mat);
}
