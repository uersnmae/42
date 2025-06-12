/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:48:12 by kim               #+#    #+#             */
/*   Updated: 2024/11/14 15:04:05 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf_bonus.h"

static void	ft_parse_flags(const char *str, int *index, t_flags *flag)
{
	while (str[*index])
	{
		if (str[*index] == '-')
			flag->left_align = 1;
		else if (str[*index] == '0')
			flag->zero_padding = 1;
		else if (str[*index] == '+')
			flag->show_sign = 1;
		else if (str[*index] == ' ')
			flag->space = 1;
		else if (str[*index] == '#')
			flag->alternate = 1;
		else
			break ;
		(*index)++;
	}
}

static void	ft_parse_width(const char *str, int *index, t_flags *flag)
{
	if (ft_isdigit(str[*index]))
	{
		flag->width = ft_atoi(&str[*index]);
		while (ft_isdigit(str[*index]))
			(*index)++;
	}
}

static void	ft_parse_precision(const char *str, int *index, t_flags *flag)
{
	if (str[*index] == '.')
	{
		(*index)++;
		flag->precision = ft_atoi(&str[*index]);
		while (ft_isdigit(str[*index]))
			(*index)++;
	}
}

void	ft_parse(const char *str, int *index, t_flags *flag)
{
	(*index)++;
	ft_parse_flags(str, index, flag);
	ft_parse_width(str, index, flag);
	ft_parse_precision(str, index, flag);
	if ((flag->precision != -1 && flag->zero_padding) || flag->left_align)
		flag->zero_padding = 0;
	flag->specifier = str[*index];
	if (flag->specifier == 'd' || flag->specifier == 'i' || \
		flag->specifier == 'u')
	{
		flag->alternate = 0;
		flag->base = DEC;
	}
	if (flag->specifier == 'x' || flag->specifier == 'X' || \
		flag->specifier == 'p')
		flag->base = HEX;
	if (flag->specifier == 'c')
	{
		flag->zero_padding = 0;
		flag->precision = -1;
		flag->show_sign = 0;
		flag->space = 0;
		flag->alternate = 0;
	}
}
