/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:47:16 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/01 13:47:43 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef object_H
# define object_H

typedef struct s_object
{
	double	angle_x;
	double	angle_y;
	double	angle_z;
	double	height_z;
	double	scale;
	int		offset_x;
	int		offset_y;
}	t_object;

#endif
