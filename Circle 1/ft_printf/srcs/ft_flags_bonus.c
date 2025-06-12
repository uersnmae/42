/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:08:29 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/24 16:07:38 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf_bonus.h"

ssize_t	ft_print_flag(t_flags *flag, va_list params)
{
	ssize_t	alternate;
	ssize_t	zero;
	ssize_t	param_width;
	ssize_t	sign;

	if (flag->specifier == 'c')
		return (0);
	alternate = ft_alternate(flag, params);
	if (alternate < 0)
		return (-1);
	sign = ft_show_sign_space(flag, params);
	if (sign < 0)
		return (-1);
	param_width = ft_get_param_width(flag, params);
	zero = 0;
	if (flag->precision > param_width)
		zero = ft_precision(flag, params, param_width);
	else if (!flag->left_align && flag->precision == -1 && flag->zero_padding)
		zero = ft_zero_padding(flag, param_width + alternate + sign);
	if (zero < 0)
		return (-1);
	return (alternate + sign + zero);
}
