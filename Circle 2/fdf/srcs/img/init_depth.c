/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_depth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:49:15 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/02 13:51:11 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

double	*init_depth(t_fdf *fdf)
{
	double	*depth;
	int		total_size;
	int		index;

	total_size = WIDTH * HEIGHT;
	depth = malloc(sizeof(double) * total_size);
	if (!depth)
		error_return(fdf, "Mallocating depth failed", NON_SYS);
	index = 0;
	while (index < total_size)
		depth[index++] = MAX_DEPTH;
	return (depth);
}
