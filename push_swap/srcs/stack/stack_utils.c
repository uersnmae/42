/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:15:18 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/14 20:08:21 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	next_up(t_stack *stk, int index)
{
	if (curr_size(stk) == 0)
		return (index);
	if (index == 0)
		return (stk->size - 1);
	else
		return (index - 1);
}

int	next_down(t_stack *stk, int index)
{
	if (curr_size(stk) == 0)
		return (index);
	if (index == stk->size - 1)
		return (0);
	else
		return (index + 1);
}

int	get_value(t_stack *stk, int index)
{
	int	i;

	i = stk->top;
	while (--index > 0)
		i = next_down(stk, i);
	return (stk->stack[i]);
}

int	curr_size(t_stack *stk)
{
	if (stk->top == stk->bottom && stk->stack[stk->top] == 0)
		return (0);
	if (stk->top > stk->bottom)
		return ((stk->size - stk->top) + (stk->bottom + 1));
	return (stk->bottom - stk->top + 1);
}

int	is_full(t_stack *stk)
{
	return (stk->size == curr_size(stk));
}
