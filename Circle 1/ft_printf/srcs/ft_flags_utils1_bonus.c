/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:46:06 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/24 16:07:18 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf_bonus.h"

static ssize_t	ft_precision_len(t_flags *flag, va_list params, \
								ssize_t param_width)
{
	ssize_t	temp;
	va_list	params_copy;

	va_copy(params_copy, params);
	temp = va_arg(params_copy, int);
	if (temp == 0 && flag->specifier == 'p')
		return (param_width);
	if (param_width - (temp == 0) <= flag->precision && flag->precision > -1)
	{
		if (flag->specifier != 'c' && flag->specifier != 's')
		{
			if (!ft_strchr("xXup", flag->specifier))
				param_width = flag->precision;
			else
				param_width = flag->precision;
			if (temp == 0 && flag->precision == 0)
				param_width = 0;
		}
	}
	va_end(params_copy);
	if (param_width >= flag->precision && flag->precision > -1)
		if (flag->specifier == 's')
			param_width = flag->precision;
	return (param_width);
}

static ssize_t	ft_get_print_len(t_flags *flag, va_list params)
{
	ssize_t	print_len;
	ssize_t	param_width;
	int		temp;
	va_list	params_copy;

	print_len = 0;
	param_width = ft_get_param_width(flag, params);
	if (flag->specifier == 'c')
		return (param_width);
	if (flag->precision > -1)
		param_width = ft_precision_len(flag, params, param_width);
	va_copy(params_copy, params);
	if ((flag->alternate && !ft_strchr("cs", flag->specifier)) || \
		(flag->specifier == 'p' && va_arg(params_copy, void *) != NULL))
		print_len += 2;
	va_end(params_copy);
	if (ft_strchr("diuxX", flag->specifier))
	{
		temp = va_arg(params, int);
		if (temp < 0 && (flag->specifier == 'd' || flag->specifier == 'i'))
			print_len += 1;
		if (temp == 0 && (flag->specifier == 'x' || flag->specifier == 'X'))
			print_len = (print_len - 2) * (flag->alternate);
	}
	return (print_len + param_width);
}

static ssize_t	ft_print_right_align(t_flags *flag, va_list params)
{
	ssize_t	printed;
	ssize_t	printed_len;
	ssize_t	temp;
	va_list	params_copy;

	printed = 0;
	va_copy(params_copy, params);
	printed_len = ft_get_print_len(flag, params_copy);
	va_end(params_copy);
	temp = ft_fill_width(flag, printed_len);
	if (temp < 0)
		return (-1);
	printed += temp;
	va_copy(params_copy, params);
	temp = ft_print_flag(flag, params_copy);
	va_end(params_copy);
	if (temp < 0)
		return (-1);
	printed += temp;
	return (printed);
}

static ssize_t	ft_print_left_align(t_flags *flag, va_list params)
{
	ssize_t	printed;
	ssize_t	temp;
	va_list	params_copy;

	printed = 0;
	va_copy(params_copy, params);
	temp = ft_print_flag(flag, params_copy);
	va_end(params_copy);
	if (temp < 0)
		return (-1);
	printed += temp;
	temp = ft_print_format(flag, params);
	if (temp < 0)
		return (-1);
	printed += temp;
	temp = ft_fill_width(flag, printed);
	if (temp < 0)
		return (-1);
	printed += temp;
	return (printed);
}

ssize_t	ft_print_params(t_flags *flag, va_list params)
{
	ssize_t	printed;
	ssize_t	temp;
	va_list	params_copy;

	printed = 0;
	if (flag->width == -1 || flag->precision == -2)
		return (-1);
	if (flag->left_align)
		printed = ft_print_left_align(flag, params);
	else if (!flag->left_align)
	{
		va_copy(params_copy, params);
		printed = ft_print_right_align(flag, params_copy);
		va_end(params_copy);
		if (printed < 0)
			return (-1);
		temp = ft_print_format(flag, params);
		if (temp < 0)
			return (-1);
		printed += temp;
	}
	return (printed);
}
