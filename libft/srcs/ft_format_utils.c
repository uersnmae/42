/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:22:01 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/24 16:10:20 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/ft_printf.h"

ssize_t	ft_putstr_printf(char *str, t_flags *flag)
{
	ssize_t	len;

	if ((str == NULL && flag->precision >= 6) || \
		(str == NULL && flag->precision == -1))
		return (write(flag->fd, "(null)", 6));
	else if (str == NULL && flag->precision < 6)
		return (0);
	else
	{
		len = ft_strlen(str);
		if ((flag->precision < len && flag->precision > 0) || \
			flag->precision == 0)
			len = flag->precision;
	}
	return (write(flag->fd, str, len));
}

static uintptr_t	ft_convert_num(t_flags *flag, long num)
{
	if (ft_strchr("diu", flag->specifier))
	{
		if (flag->specifier == 'u')
			return ((unsigned int)num);
		else
		{
			if (num < 0)
				return ((unsigned int)(-num));
			else
				return ((unsigned int)num);
		}
	}
	if (ft_strchr("xXp", flag->specifier))
	{
		if (flag->specifier == 'p')
			return ((uintptr_t)num);
		else
			return ((unsigned int)num);
	}
	return (0);
}

static void	ft_fill_buf(t_flags *flag, char *buf, uintptr_t n, ssize_t buf_len)
{
	if (n == 0)
	{
		buf[--buf_len] = '0';
		return ;
	}
	while (n > 0)
	{
		if (flag->specifier == 'X')
			buf[--buf_len] = "0123456789ABCDEF"[n % flag->base];
		else
			buf[--buf_len] = "0123456789abcdef"[n % flag->base];
		n /= flag->base;
	}
}

ssize_t	ft_putnum_printf(t_flags *flag, long num)
{
	ssize_t		buf_len;
	ssize_t		ret;
	uintptr_t	n;
	char		*buf;

	ret = 0;
	if (num == 0 && flag->specifier == 'p')
		return (write(flag->fd, "(nil)", 5));
	if (flag->precision == 0 && num == 0)
		return (0);
	n = ft_convert_num(flag, num);
	buf_len = ft_numlen(flag, n, UNSIGNED);
	buf = malloc(buf_len);
	if (!buf || (num != 0 && n == 0) || (num == 0 && flag->precision == 0))
		return (-1 + (num == 0 && flag->precision == 0));
	ft_fill_buf(flag, buf, n, buf_len);
	ret += write(flag->fd, buf, buf_len);
	free(buf);
	return (ret);
}
