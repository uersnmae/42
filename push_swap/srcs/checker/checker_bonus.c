/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:11:34 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/19 14:28:22 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static bool	is_empty(t_stack stk)
{
	return (curr_size(&stk) == 0);
}

int	main(int argc, char **argv)
{
	t_ps	data;
	bool	sorted;

	init_data(&data, argc, argv, false);
	read_ops(&data);
	sorted = is_sorted(&data);
	if (!is_sorted(&data) || !is_empty(data.b))
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
	free_data(&data);
	return (0);
}
