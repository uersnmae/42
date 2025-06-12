/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orthographic_projection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:55:42 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/01 14:08:47 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_ortho(t_ortho *ortho)
{
	ortho->left = -WIDTH / 2.0;
	ortho->right = WIDTH / 2.0;
	ortho->bottom = -HEIGHT / 2.0;
	ortho->top = HEIGHT / 2.0;
	ortho->near = -1000.0;
	ortho->far = 1000.0;
}

t_matrix	create_ortho_projection(t_ortho *ortho)
{
	t_matrix	proj;

	proj = matrix_identity();
	proj.m[0][0] = 2.0 / (ortho->right - ortho->left);
	proj.m[1][1] = 2.0 / (ortho->top - ortho->bottom);
	proj.m[2][2] = -2.0 / (ortho->far - ortho->near);
	proj.m[0][3] = -(ortho->right + ortho->left) / (ortho->right - ortho->left);
	proj.m[1][3] = -(ortho->top + ortho->bottom) / (ortho->top - ortho->bottom);
	proj.m[2][3] = -(ortho->far + ortho->near) / (ortho->far - ortho->near);
	return (proj);
}
