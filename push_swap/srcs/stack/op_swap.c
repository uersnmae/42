/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:15:07 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/14 14:00:30 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	swap(t_stack *stk)
{
	int	temp;

	if (stk->stack[next_down(stk, stk->top)] == 0)
		return ;
	temp = stk->stack[stk->top];
	stk->stack[stk->top] = stk->stack[next_down(stk, stk->top)];
	stk->stack[next_down(stk, stk->top)] = temp;
}

void	swap_a(t_ps *data)
{
	swap(&data->a);
	if (data->writing_mode)
		save_op(data, sa);
}

void	swap_b(t_ps *data)
{
	swap(&data->b);
	if (data->writing_mode)
		save_op(data, sb);
}
