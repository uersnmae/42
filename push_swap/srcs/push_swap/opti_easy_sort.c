/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_easy_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:12:14 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/17 11:16:12 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	handle_bottom_b(t_ps *data, t_chunk *to_sort)
{
	rotate_reverse_b(data);
	rotate_reverse_b(data);
	push_a(data);
	if (get_value(&data->b, 1) == get_value(&data->a, 1) - 1)
	{
		push_a(data);
		to_sort->size--;
	}
	else
		rotate_b(data);
}

static void	handle_bottom_a(t_ps *data, t_chunk *to_sort)
{
	rotate_reverse_a(data);
	rotate_reverse_a(data);
	swap_a(data);
	if (get_value(&data->a, 1) == get_value(&data->a, 2) - 1)
		to_sort->size--;
	else
		rotate_a(data);
}

static void	handle_top_b(t_ps *data, t_chunk *to_sort)
{
	swap_b(data);
	push_a(data);
	if (get_value(&data->b, 1) == get_value(&data->a, 1) - 1)
	{
		push_a(data);
		to_sort->size--;
	}
}

static void	easy_sort_second(t_ps *data, t_chunk *to_sort)
{
	if (to_sort->loc == TOP_B)
		handle_top_b(data, to_sort);
	else if (to_sort->loc == BOTTOM_A)
		handle_bottom_a(data, to_sort);
	else if (to_sort->loc == BOTTOM_B)
		handle_bottom_b(data, to_sort);
	to_sort->size--;
}

void	easy_sort(t_ps *data, t_chunk *to_sort)
{
	while (to_sort->loc != TOP_A && to_sort->size)
	{
		if (get_value(&data->a, 1) == chunk_value(data, to_sort, 1) - 1
			&& to_sort->size > 0)
			sort_one(data, to_sort);
		else if (get_value(&data->a, 1) == chunk_value(data, to_sort, 2) - 1
			&& to_sort->size > 1)
			easy_sort_second(data, to_sort);
		else
			break ;
	}
}
