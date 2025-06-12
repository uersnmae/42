/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:37:58 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/24 16:09:34 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

size_t	ft_numlen(t_flags *flag, long nbr, int sign)
{
	size_t		len;
	uintptr_t	pnbr;

	len = 1;
	if (flag->precision == 0 && nbr == 0)
		return (0);
	if (nbr < 0 && sign == SIGNED && flag->base == DEC)
		pnbr = (uintptr_t)(-nbr);
	else if (flag->specifier == 'p')
	{
		pnbr = (uintptr_t)nbr;
		if (pnbr == 0)
			return (0);
	}
	else
		pnbr = (unsigned int)nbr;
	while (pnbr >= (uintptr_t)flag->base)
	{
		len++;
		pnbr /= flag->base;
	}
	return (len);
}

ssize_t	ft_print_format(t_flags *flag, va_list params)
{
	unsigned char	c;

	c = 0;
	if (flag->specifier == 'c')
	{
		c = (unsigned char)va_arg(params, int);
		return (write(flag->fd, &c, 1));
	}
	else if (flag->specifier == 's')
		return (ft_putstr_printf(va_arg(params, char *), flag));
	else if (flag->specifier == 'p')
		return (ft_putnum_printf(flag, (uintptr_t)va_arg(params, void *)));
	else if (ft_strchr("diu", flag->specifier))
		return (ft_putnum_printf(flag, va_arg(params, int)));
	else if (flag->specifier == 'x')
		return (ft_putnum_printf(flag, va_arg(params, int)));
	else if (flag->specifier == 'X')
		return (ft_putnum_printf(flag, va_arg(params, int)));
	else if (flag->specifier == '%')
		return (write(flag->fd, "%", 1));
	else
		return (-1);
}
