/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:13:06 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/14 15:04:51 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf_bonus.h"

static ssize_t	ft_get_param_width_callback(t_flags *flag, va_list params)
{
	void	*buf;

	if (flag->specifier == 's' || flag->specifier == 'p')
	{
		buf = va_arg(params, void *);
		if (buf == NULL)
			return (6 * (flag->precision >= 6 || flag->precision == -1 || \
			flag->specifier == 'p') - (flag->specifier == 'p'));
		if (flag->specifier == 'p')
			return (ft_numlen(flag, (uintptr_t)buf, UNSIGNED));
		if ((ssize_t)ft_strlen(buf) > flag->precision && flag->precision != -1)
			return (flag->precision);
		if ((ssize_t)ft_strlen(buf) <= flag->precision || flag->precision == -1)
			return (ft_strlen(buf));
	}
	else if (flag->specifier == 'c')
		return (1);
	else if (flag->specifier == 'd' || flag->specifier == 'i')
		return (ft_numlen(flag, va_arg(params, int), SIGNED));
	else if (flag->specifier == 'u')
		return (ft_numlen(flag, va_arg(params, int), UNSIGNED));
	else if (flag->specifier == 'x' || flag->specifier == 'X')
		return (ft_numlen(flag, va_arg(params, int), UNSIGNED));
	return (0);
}

ssize_t	ft_get_param_width(t_flags *flag, va_list params)
{
	ssize_t	ret;
	va_list	params_copy;

	va_copy(params_copy, params);
	ret = ft_get_param_width_callback(flag, params_copy);
	va_end(params_copy);
	return (ret);
}
