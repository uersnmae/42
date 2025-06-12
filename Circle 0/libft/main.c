/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:29:19 by dong-hki          #+#    #+#             */
/*   Updated: 2024/11/14 15:33:00 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/ft_printf_bonus.h"

int	main(void)
{
	int		a;
	int		b;
	int		num;
	void	*ptr;

	num = 42;
	ptr = NULL;
	a = printf("|%64.32p|\n", ptr);
	b = ft_printf("|%64.32p|\n", ptr);
	printf("%d %d", a, b);
	return (0);
}
