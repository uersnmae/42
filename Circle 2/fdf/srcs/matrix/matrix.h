/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:54:52 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/01 14:03:36 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "object.h"
# include "map.h"
# include "camera.h"

# define ROW	4
# define COL	4

typedef int		t_mat_index;
typedef struct s_matrix
{
	double	m[4][4];
}	t_matrix;

typedef struct s_ortho
{
	double	left;
	double	right;
	double	top;
	double	bottom;
	double	near;
	double	far;
}	t_ortho;

// model_matrix
t_matrix	compute_model_matrix(t_map *map, t_object *object);

// view_matrix
t_matrix	compute_view_matrix(t_camera *cam);

// orthogrphic_projection
void		init_ortho(t_ortho *ortho);
t_matrix	create_ortho_projection(t_ortho *ortho);

// rotate_matrix
t_matrix	matrix_x_rotate(double radian);
t_matrix	matrix_y_rotate(double radian);
t_matrix	matrix_z_rotate(double radian);

// utils_matrix
t_matrix	matrix_identity(void);
t_matrix	matrix_multiply(t_matrix a, t_matrix b);
t_matrix	matrix_translation(double tx, double ty, double tz);
t_matrix	matrix_scaling(double sx, double sy, double sz);

#endif
