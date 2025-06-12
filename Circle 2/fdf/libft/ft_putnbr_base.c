/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:21:00 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/25 15:23:08 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static unsigned int	ft_get_base(char *base)
{
	int	index1;
	int	index2;

	index1 = 0;
	if (base[index1] == '+' || base[index1] == '-')
		return (0);
	while (base[index1] != '\0')
	{
		index2 = index1 + 1;
		while (base[index2] != '\0')
		{
			if (base[index2] == '+' || base[index2] == '-')
				return (0);
			if (base[index1] == base[index2])
				return (0);
			index2++;
		}
		index1++;
	}
	return (index1);
}

static void	ft_putnbr(int nb, unsigned int base_len, char *base)
{
	unsigned int	_nb;

	if (nb < 0)
	{
		ft_putchar_fd('-', STDOUT_FILENO);
		_nb = -nb;
	}
	else
		_nb = nb;
	if (_nb >= base_len)
		ft_putnbr(_nb / base_len, base_len, base);
	ft_putchar_fd(base[_nb % base_len], STDOUT_FILENO);
}

void	ft_putnbr_base(int nbr, char *base)
{
	unsigned int	base_len;

	base_len = ft_get_base(base);
	write(STDOUT_FILENO, "0x", 2);
	if (base_len <= 1)
		return ;
	ft_putnbr(nbr, base_len, base);
	return ;
}
