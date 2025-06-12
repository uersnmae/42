/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:14:11 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/24 19:08:49 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_radian(double num)
{
	return (num * PI / 180.0);
}

int	get_min(int x, int y)
{
	if (x >= y)
		return (y);
	else
		return (x);
}
