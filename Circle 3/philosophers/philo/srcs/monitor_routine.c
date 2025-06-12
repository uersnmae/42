/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:32:46 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/03 15:10:35 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>

#include "philo.h"
#include "philo_type.h"

static void	set_philo_state(t_table *table, bool state);
static bool	philo_dead(t_philo *philo);
static bool	is_all_eat_enough(t_table *table);

void	*monitor_routine(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	set_philo_state(table, false);
	wait_delay(table->start_time);
	while (true)
	{
		if (is_all_eat_enough(table) == true)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

bool	is_philo_stop(t_table *table)
{
	bool	flag;

	flag = false;
	pthread_mutex_lock(&table->monitor_lock);
	if (table->philo_stop == true)
		flag = true;
	pthread_mutex_unlock(&table->monitor_lock);
	return (flag);
}

static void	set_philo_state(t_table *table, bool state)
{
	pthread_mutex_lock(&table->monitor_lock);
	table->philo_stop = state;
	pthread_mutex_unlock(&table->monitor_lock);
}

static bool	philo_dead(t_philo *philo)
{
	time_t	current;

	current = get_time_in_ms();
	if ((current - philo->last_meal) >= philo->table->info[INFO_TIME_TO_DIE])
	{
		set_philo_state(philo->table, true);
		pthread_mutex_unlock(&philo->meal_lock);
		philo_print_state(philo, STATUS_DEAD);
		return (true);
	}
	return (false);
}

static bool	is_all_eat_enough(t_table *table)
{
	int		index;
	bool	eat_enough;

	eat_enough = true;
	index = 0;
	while (index < table->info[INFO_NUMBER_OF_PHILOSOPHERS])
	{
		pthread_mutex_lock(&table->philo[index].meal_lock);
		if (philo_dead(&table->philo[index]) == true)
			return (true);
		if (table->info[INFO_NUMBER_OF_TIMES_EACH_PHILOSOHPER_MUST_EAT] != -1 \
			&& table->philo[index].eat_count < \
			table->info[INFO_NUMBER_OF_TIMES_EACH_PHILOSOHPER_MUST_EAT])
			eat_enough = false;
		pthread_mutex_unlock(&table->philo[index].meal_lock);
		index++;
	}
	if (table->info[INFO_NUMBER_OF_TIMES_EACH_PHILOSOHPER_MUST_EAT] != -1 && \
		eat_enough == true)
	{
		set_philo_state(table, true);
		return (true);
	}
	return (false);
}
