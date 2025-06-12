/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:40:59 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/31 16:23:36 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <limits.h>

int	get_num(char *str)
{
	long	result;
	int		neg_flag;
	int		index;

	result = 0;
	neg_flag = 1;
	index = 0;
	while (((str[index] >= 9 && str[index] <= 13) || str[index] == ' '))
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index++] == '-')
			neg_flag *= -1;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		if (result * 10 + (str[index] - '0') > 2147483648 && neg_flag == -1)
			return (0);
		if (result * 10 + (str[index] - '0') > 2147483647 && neg_flag == 1)
			return (0);
		result = result * 10 + (str[index] - '0');
		index++;
	}
	return ((int)result * neg_flag);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
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

int	is_unsigned_num(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isdigit((int)str[index++]) != 1)
			return (0);
	}
	return (1);
}
