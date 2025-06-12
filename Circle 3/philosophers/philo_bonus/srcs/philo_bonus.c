/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:02:53 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/30 16:36:24 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "philo_bonus.h"
#include "philo_bonus_type.h"

#define MAX_MAIN_ROUTINE	3

typedef int	(*t_routine)(t_table *table);

static void	__start_main(t_table *table)
{
	const t_routine	main_routine_table[] = \
		{init_semaphores, init_philo, wait_philo, NULL};
	int				i;

	i = 0;
	while (i < MAX_MAIN_ROUTINE)
	{
		if (main_routine_table[i++](table) != 0)
		{
			free_table(table);
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (error_status(STR_ERR_USAGE, NULL, NULL));
	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (error_status(STR_ERR_MALLOC, NULL, NULL));
	memset(table, 0, sizeof(t_table));
	if (init_info(table, argv + 1) != 0)
		return (EXIT_FAILURE);
	if (table->info[INFO_NUMBER_OF_TIMES_EACH_PHILOSOHPER_MUST_EAT] == 0)
	{
		free_table(table);
		return (EXIT_SUCCESS);
	}
	__start_main(table);
	free_table(table);
	return (EXIT_SUCCESS);
}
