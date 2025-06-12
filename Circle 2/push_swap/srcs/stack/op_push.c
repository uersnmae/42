/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:05:07 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/14 14:00:06 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	push(t_stack *dest, t_stack *src)
{
	int	dest_i;

	if (is_full(dest))
		return ;
	dest_i = next_up(dest, dest->top);
	dest->stack[dest_i] = src->stack[src->top];
	dest->top = dest_i;
	src->stack[src->top] = 0;
	src->top = next_down(src, src->top);
}

void	push_a(t_ps *data)
{
	push(&data->a, &data->b);
	if (data->writing_mode)
		save_op(data, pa);
}

void	push_b(t_ps *data)
{
	push(&data->b, &data->a);
	if (data->writing_mode)
		save_op(data, pb);
}
