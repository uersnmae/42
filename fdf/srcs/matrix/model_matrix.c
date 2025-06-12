/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:16:23 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/01 13:38:46 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

#define X	0L
#define Y	1L

static t_matrix	rotate_model(t_object *object);

t_matrix	compute_model_matrix(t_map *map, t_object *object)
{
	double		center[2];
	t_matrix	translation;
	t_matrix	scaling;
	t_matrix	model;
	t_matrix	rotation;

	center[X] = (map->width * object->scale) / 2.0;
	center[Y] = (map->height * object->scale) / 2.0;
	translation = matrix_translation(-center[X], -center[Y], 0);
	scaling = matrix_scaling(object->scale, object->scale, object->scale);
	rotation = rotate_model(object);
	model = matrix_multiply(translation, matrix_multiply(rotation, scaling));
	return (model);
}

static t_matrix	rotate_model(t_object *object)
{
	t_matrix	mat;
	t_matrix	rot_x;
	t_matrix	rot_y;
	t_matrix	rot_z;

	rot_x = matrix_x_rotate(object->angle_x);
	rot_y = matrix_y_rotate(object->angle_y);
	rot_z = matrix_z_rotate(object->angle_z);
	mat = matrix_multiply(rot_z, matrix_multiply(rot_y, rot_x));
	return (mat);
}
