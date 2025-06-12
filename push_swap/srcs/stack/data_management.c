/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:05:19 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/19 14:08:18 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	init_data(t_ps *data, int argc, char *argv[], bool flag)
{
	char	**splited;
	int		splited_size;

	data->op_list = NULL;
	data->writing_mode = flag;
	if (argc == 2)
	{
		splited_size = 0;
		splited = ft_split(argv[1], ' ');
		splited_size = valid_split(splited);
		init_stack(data, &data->a, splited_size);
		init_stack(data, &data->b, splited_size);
		fill_stack(data, &data->a, splited_size, splited);
		free_split(splited);
	}
	else
	{
		--argc;
		init_stack(data, &data->a, argc);
		init_stack(data, &data->b, argc);
		fill_stack(data, &data->a, argc, ++argv);
	}
}

void	init_stack(t_ps *data, t_stack *stk, int size)
{
	stk->stack = malloc(sizeof(int) * size);
	if (!stk->stack)
		error(data);
	stk->size = size;
	stk->top = 0;
	stk->bottom = 0;
	ft_memset(stk->stack, 0, (sizeof(int) * stk->size));
}

bool	is_sorted(t_ps *data)
{
	int	i;
	int	rank;

	i = data->a.top;
	rank = 1;
	while (rank <= data->a.size)
	{
		if (data->a.stack[i] != rank)
			return (false);
		rank++;
		i = next_down(&data->a, i);
	}
	return (true);
}

void	error(t_ps *data)
{
	free_data(data);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	free_data(t_ps *data)
{
	if (data->a.stack)
		free(data->a.stack);
	if (data->b.stack)
		free(data->b.stack);
	if (data->op_list)
		ft_lstclear(&data->op_list, NULL);
}
