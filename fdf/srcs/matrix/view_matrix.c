/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:37:30 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/01 14:17:58 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	compute_view_matrix(t_camera *cam)
{
	t_matrix	translation;
	t_matrix	rot_x;
	t_matrix	rot_y;
	t_matrix	rot_z;
	t_matrix	view;

	translation = matrix_translation(-cam->pos_x, -cam->pos_y, -cam->pos_z);
	rot_x = matrix_x_rotate(-cam->rot_x);
	rot_y = matrix_y_rotate(-cam->rot_y);
	rot_z = matrix_z_rotate(-cam->rot_z);
	view = matrix_multiply(rot_z, \
		matrix_multiply(rot_y, \
		matrix_multiply(rot_x, translation)));
	return (view);
}
