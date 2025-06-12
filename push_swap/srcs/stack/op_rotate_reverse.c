/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rotate_reverse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:43:23 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/14 14:00:24 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	rotate_reverse(t_stack *stk)
{
	if (is_full(stk))
	{
		stk->top = stk->bottom;
		stk->bottom = next_up(stk, stk->bottom);
	}
	else
	{
		stk->top = next_up(stk, stk->top);
		stk->stack[stk->top] = stk->stack[stk->bottom];
		stk->stack[stk->bottom] = 0;
		stk->bottom = next_up(stk, stk->bottom);
	}
}

void	rotate_reverse_a(t_ps *data)
{
	rotate_reverse(&data->a);
	if (data->writing_mode)
		save_op(data, rra);
}

void	rotate_reverse_b(t_ps *data)
{
	rotate_reverse(&data->b);
	if (data->writing_mode)
		save_op(data, rrb);
}

void	rotate_reverse_all(t_ps *data)
{
	rotate_reverse(&data->a);
	rotate_reverse(&data->b);
	if (data->writing_mode)
		save_op(data, rrr);
}
