/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_sort_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:29:46 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/18 11:25:28 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three_top_a(t_ps *data,
							t_chunk *to_sort, t_stack *stk, int max)
{
	if (stk->stack[stk->top] == max)
	{
		swap_a(data);
		rotate_a(data);
		swap_a(data);
		rotate_reverse_a(data);
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		rotate_a(data);
		swap_a(data);
		rotate_reverse_a(data);
	}
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

static void	sort_three_top_b(t_ps *data,
							t_chunk *to_sort, t_stack *stk, int max)
{
	push_a(data);
	if (stk->stack[stk->top] == max)
	{
		push_a(data);
		swap_a(data);
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		rotate_a(data);
		swap_a(data);
		rotate_reverse_a(data);
	}
	else
		push_a(data);
	push_a(data);
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

static void	sort_three_bottom_a(t_ps *data,
								t_chunk *to_sort, t_stack *stk, int max)
{
	rotate_reverse_a(data);
	rotate_reverse_a(data);
	if (stk->stack[stk->top] == max)
	{
		swap_a(data);
		rotate_reverse_a(data);
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
		rotate_reverse_a(data);
	else
	{
		push_b(data);
		rotate_reverse_a(data);
		swap_a(data);
		push_a(data);
	}
	to_sort->loc = TOP_A;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

static void	sort_three_bottom_b(t_ps *data,
								t_chunk *to_sort, t_stack *stk, int max)
{
	rotate_reverse_b(data);
	rotate_reverse_b(data);
	if (stk->stack[stk->top] == max)
	{
		push_a(data);
		rotate_reverse_b(data);
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		swap_b(data);
		push_a(data);
		rotate_reverse_b(data);
	}
	else
	{
		rotate_reverse_b(data);
		push_a(data);
	}
	to_sort->loc = TOP_B;
	to_sort->size -= 1;
	sort_two(data, to_sort);
}

void	sort_three(t_ps *data, t_chunk *to_sort)
{
	t_stack	*stk;
	int		max;

	stk = loc_to_stack(data, to_sort->loc);
	max = chunk_max_value(data, to_sort);
	if (to_sort->loc == TOP_A)
		sort_three_top_a(data, to_sort, stk, max);
	else if (to_sort->loc == TOP_B)
		sort_three_top_b(data, to_sort, stk, max);
	else if (to_sort->loc == BOTTOM_A)
		sort_three_bottom_a(data, to_sort, stk, max);
	else
		sort_three_bottom_b(data, to_sort, stk, max);
}
