/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:47:30 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/30 11:27:50 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philo.h"

#define __ROUTINE_NUM 3

int	main(int argc, char *argv[])
{
	static int	routine_index;
	static int	(*__routine[])(t_table *table) = \
		{init_mutex, init_philo, join_philo};
	t_table		*table;

	if (argc != 5 && argc != 6)
	{
		printf(STR_ERR_USAGE, STR_PROG_NAME);
		return (EXIT_FAILURE);
	}
	table = malloc(sizeof(t_table));
	if (!table)
		return (error_status(STR_ERR_MALLOC, NULL, table));
	if (init_info(table, argv + 1) != 0)
		return (EXIT_FAILURE);
	while (routine_index < __ROUTINE_NUM)
	{
		if (__routine[routine_index++](table) != 0)
		{
			free_table(table);
			return (EXIT_FAILURE);
		}
	}
	free_table(table);
	return (EXIT_SUCCESS);
}
