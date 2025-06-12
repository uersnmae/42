/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:20:36 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/22 11:20:36 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skip_to_num(char *str, int *index, int *neg_flag);
static int	ft_get_base(char *base);
static int	ft_return_base(char c, char *base);
static void	ft_skip_to_num(char *str, int *index, int *neg_flag);

int	ft_atoi_base(char *str, char *base)
{
	int	base_len;
	int	result;
	int	neg_flag;
	int	index;

	base_len = ft_get_base(base);
	result = 0;
	neg_flag = 1;
	index = 0;
	if (base_len <= 1)
		return (0);
	ft_skip_to_num(str, &index, &neg_flag);
	while (ft_return_base(str[index], base) != -1)
	{
		result = result * base_len + ft_return_base(str[index], base);
		index++;
	}
	return (result * neg_flag);
}

static int	ft_get_base(char *base)
{
	int	index1;
	int	index2;

	index1 = 0;
	if (base[index1] == '+' || base[index1] == '-' || \
		(base[index1] >= 9 && base[index1] <= 13) || base[index1] == ' ')
		return (0);
	while (base[index1] != '\0')
	{
		index2 = index1 + 1;
		while (base[index2] != '\0')
		{
			if (base[index2] == '+' || base[index2] == '-' || \
			(base[index2] >= 9 && base[index2] <= 13) || base[index2] == ' ')
				return (0);
			if (base[index1] == base[index2])
				return (0);
			index2++;
		}
		index1++;
	}
	return (index1);
}

static int	ft_return_base(char c, char *base)
{
	int	index;

	index = 0;
	if (c >= 'a' && c <= 'z')
		c -= 32;
	while (base[index] != '\0')
	{
		if (c == base[index])
			return (index);
		index++;
	}
	return (-1);
}

static void	ft_skip_to_num(char *str, int *index, int *neg_flag)
{
	while ((str[*index] >= 9 && str[*index] <= 13) || str[*index] == ' ')
		*index += 1;
	while (str[*index] == '+' || str[*index] == '-')
	{
		if (str[*index] == '-')
			*neg_flag *= (-1);
		*index += 1;
	}
	if (ft_strncmp(str + *index, "0x", 2) == 0)
		*index += 2;
}
