/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:04:51 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/26 18:00:26 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	ranking(int *numbers, int *stack, int size)
{
	int	i;
	int	j;
	int	min_counter;

	i = 0;
	while (i < size)
	{
		j = 0;
		min_counter = 0;
		while (j < size)
			if (numbers[j++] <= numbers[i])
				min_counter++;
		stack[i++] = min_counter;
	}
}

bool	valid_arg(char *arg)
{
	long long	num;
	int			sign;

	sign = 1;
	num = 0;
	if (*arg == '\0')
		return (false);
	if (*arg == '+' || *arg == '-')
		if (*(arg++) == '-')
			sign = -1;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (false);
		num = num * 10 + (*arg - '0');
		if ((sign == 1 && num > INT_MAX)
			|| (sign == -1 && num * sign < INT_MIN))
			return (false);
		arg++;
	}
	return (true);
}

static void	duplication_check(t_ps *data, int *numbers, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (numbers[i] == numbers[j])
			{
				free(numbers);
				error(data);
			}
			++j;
		}
		++i;
	}
}

void	fill_stack(t_ps *data, t_stack *stk, int size, char *argv[])
{
	int	*numbers;
	int	i;

	numbers = (int *)malloc(sizeof(int) * size);
	if (!numbers)
		error(data);
	i = 0;
	while (argv[i])
	{
		if (!valid_arg(argv[i]))
		{
			free(numbers);
			error(data);
		}
		numbers[i] = ft_atoi(argv[i]);
		i++;
	}
	duplication_check(data, numbers, size);
	ranking(numbers, stk->stack, size);
	stk->bottom = size - 1;
	free(numbers);
}
