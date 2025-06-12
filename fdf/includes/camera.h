/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:46:24 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/01 13:46:54 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_camera
{
	double	rot_x;
	double	rot_y;
	double	rot_z;
	double	pos_x;
	double	pos_y;
	double	pos_z;
	int		toggle;
}	t_camera;

#endif
