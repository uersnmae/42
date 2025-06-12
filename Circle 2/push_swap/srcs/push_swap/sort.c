/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:32:30 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/15 15:49:18 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"

static void	sort_three_a(t_ps *data)
{
	int	tmp[3];

	tmp[0] = get_value(&data->a, 1);
	tmp[1] = get_value(&data->a, 2);
	tmp[2] = get_value(&data->a, 3);
	if (tmp[0] < tmp[1] && tmp[1] > tmp[2] && tmp[0] < tmp[2])
	{
		rotate_reverse_a(data);
		swap_a(data);
	}
	else if (tmp[0] > tmp[1] && tmp[1] < tmp[2] && tmp[0] < tmp[2])
		swap_a(data);
	else if (tmp[0] < tmp[1] && tmp[1] > tmp[2] && tmp[0] > tmp[2])
		rotate_reverse_a(data);
	else if (tmp[0] > tmp[1] && tmp[1] < tmp[2] && tmp[0] > tmp[2])
		rotate_a(data);
	else if (tmp[0] > tmp[1] && tmp[1] > tmp[2] && tmp[0] > tmp[2])
	{
		swap_a(data);
		rotate_reverse_a(data);
	}
}

static void	sort_five_a(t_ps *data)
{
	while (curr_size(&data->a) > 4)
	{
		if (get_value(&data->a, 1) == 1 || get_value(&data->a, 1) == 2)
			push_b(data);
		else
			rotate_a(data);
	}
	sort_three_a(data);
	if (get_value(&data->b, 1) < get_value(&data->b, 2))
		swap_b(data);
	push_a(data);
	push_a(data);
}

void	sort(t_ps *data)
{
	if (data->a.size <= 1 || is_sorted(data))
		return ;
	else if (data->a.size == 3)
		sort_three_a(data);
	else if (data->a.size == 5)
		sort_five_a(data);
	else
		chunk_sort(data);
}
