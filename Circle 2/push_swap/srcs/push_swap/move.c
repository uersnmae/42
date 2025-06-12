/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:24:00 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/14 15:19:48 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	move_from_top_a(t_ps *data, enum e_loc to)
{
	if (to == TOP_B)
		push_b(data);
	else if (to == BOTTOM_B)
	{
		push_b(data);
		rotate_b(data);
	}
	else if (to == BOTTOM_A)
		rotate_a(data);
}

static void	move_from_top_b(t_ps *data, enum e_loc to)
{
	if (to == TOP_A)
		push_a(data);
	else if (to == BOTTOM_A)
	{
		push_a(data);
		rotate_a(data);
	}
	else if (to == BOTTOM_B)
		rotate_b(data);
}

static void	move_from_bottom_a(t_ps *data, enum e_loc to)
{
	if (to == TOP_A)
		rotate_reverse_a(data);
	else if (to == TOP_B)
	{
		rotate_reverse_a(data);
		push_b(data);
	}
	else if (to == BOTTOM_B)
	{
		rotate_reverse_a(data);
		push_b(data);
		rotate_b(data);
	}
}

static void	move_from_bottom_b(t_ps *data, enum e_loc to)
{
	if (to == TOP_A)
	{
		rotate_reverse_b(data);
		push_a(data);
	}
	else if (to == TOP_B)
		rotate_reverse_b(data);
	else if (to == BOTTOM_A)
	{
		rotate_reverse_b(data);
		push_a(data);
		rotate_a(data);
	}
}

int	move_from_to(t_ps *data, enum e_loc from, enum e_loc to)
{
	if (from == TOP_A)
		move_from_top_a(data, to);
	else if (from == TOP_B)
		move_from_top_b(data, to);
	else if (from == BOTTOM_A)
		move_from_bottom_a(data, to);
	else if (from == BOTTOM_B)
		move_from_bottom_b(data, to);
	return (1);
}
