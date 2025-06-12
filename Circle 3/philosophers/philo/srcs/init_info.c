/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:32:40 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/31 16:25:18 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "philo.h"
#include "philo_type.h"

int	init_info(t_table *table, char *argv[])
{
	int		index;

	index = 0;
	memset(table, 0, sizeof(t_table));
	while (argv[index] != NULL)
	{
		if (!valid_arg(argv[index]) || is_unsigned_num(argv[index]) != 1)
			return (error_status(STR_ERR_INPUT_DIGIT, argv[index], table));
		table->info[index] = get_num(argv[index]);
		++index;
	}
	if (table->info[INFO_NUMBER_OF_PHILOSOPHERS] < 1 || \
		table->info[INFO_NUMBER_OF_PHILOSOPHERS] >= 250)
		return (error_status(STR_ERR_INPUT_POFLOW, "250", table));
	if (index == 4)
		table->info[index] = -1;
	table->philo_stop = false;
	return (0);
}

int	init_mutex(t_table *table)
{
	int	index;

	table->fork_lock = malloc(sizeof(pthread_mutex_t) * \
					table->info[INFO_NUMBER_OF_PHILOSOPHERS]);
	if (!table->fork_lock)
		return (error_status(STR_ERR_MALLOC, NULL, table));
	index = 0;
	while (index < table->info[INFO_NUMBER_OF_PHILOSOPHERS])
	{
		if (pthread_mutex_init(&table->fork_lock[index], NULL) != 0)
			return (error_status(STR_ERR_MUTEX, NULL, table));
		++index;
	}
	if (pthread_mutex_init(&table->write_lock, NULL) != 0 || \
		pthread_mutex_init(&table->monitor_lock, NULL) != 0)
		return (error_status(STR_ERR_MUTEX, NULL, table));
	return (0);
}

int	init_philo(t_table *table)
{
	static int	index;

	table->philo = malloc(sizeof(t_philo) * \
					table->info[INFO_NUMBER_OF_PHILOSOPHERS]);
	if (!table->philo)
		return (error_status(STR_ERR_MALLOC, NULL, table));
	table->start_time = get_time_in_ms() + \
		table->info[INFO_NUMBER_OF_PHILOSOPHERS] * 20;
	while (index < table->info[INFO_NUMBER_OF_PHILOSOPHERS])
	{
		table->philo[index].table = table;
		table->philo[index].philo_index = index;
		table->philo[index].last_meal = table->start_time;
		table->philo[index].eat_count = 0;
		pthread_mutex_init(&table->philo[index].meal_lock, NULL);
		get_fork_index(&table->philo[index]);
		if (pthread_create(&table->philo[index].philosopher, \
					NULL, philo_routine, &table->philo[index]) != 0)
			return (error_status(STR_ERR_THREAD, NULL, table));
		index++;
	}
	if (pthread_create(&table->monitor, \
		NULL, monitor_routine, table) != 0)
		return (error_status(STR_ERR_THREAD, NULL, table));
	return (0);
}

int	join_philo(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->info[INFO_NUMBER_OF_PHILOSOPHERS])
	{
		if (pthread_join(table->philo[index].philosopher, NULL) != 0)
			return (error_status(STR_ERR_THREAD, NULL, table));
		++index;
	}
	if (pthread_join(table->monitor, NULL) != 0)
		return (error_status(STR_ERR_THREAD, NULL, table));
	return (0);
}
