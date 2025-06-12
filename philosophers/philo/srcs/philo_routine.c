/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:02:10 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/03 10:30:05 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philo.h"
#include "philo_type.h"

static void	philo_eat_and_sleep(t_philo *philo, t_table *table);
static void	philo_think(t_philo *philo, t_table *table, bool flag);

void	*philo_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	if (table->info[INFO_NUMBER_OF_TIMES_EACH_PHILOSOHPER_MUST_EAT] == 0)
		return (NULL);
	wait_delay(table->start_time);
	if (table->info[INFO_NUMBER_OF_PHILOSOPHERS] == 1)
		return (lone_philo_routine(philo));
	if (philo->philo_index % 2 == 1)
		philo_think(philo, table, true);
	while (is_philo_stop(table) == false)
	{
		philo_eat_and_sleep(philo, table);
		philo_think(philo, table, false);
	}
	return (NULL);
}

static void	philo_eat_and_sleep(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->fork_lock[philo->fork_index[0]]);
	philo_print_state(philo, STATUS_PICK_FORK_1);
	pthread_mutex_lock(&table->fork_lock[philo->fork_index[1]]);
	philo_print_state(philo, STATUS_PICK_FORK_2);
	philo_print_state(philo, STATUS_EAT);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	nonblock_sleep(table, table->info[INFO_TIME_TO_EAT]);
	if (is_philo_stop(table) == false)
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->meal_lock);
	}
	pthread_mutex_unlock(&table->fork_lock[philo->fork_index[1]]);
	pthread_mutex_unlock(&table->fork_lock[philo->fork_index[0]]);
	philo_print_state(philo, STATUS_SLEEP);
	nonblock_sleep(table, table->info[INFO_TIME_TO_SLEEP]);
}

static void	philo_think(t_philo *philo, t_table *table, bool flag)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_lock);
	time_to_think = (table->info[INFO_TIME_TO_DIE] \
					- (get_time_in_ms() - philo->last_meal) \
					- table->info[INFO_TIME_TO_EAT]) / 2;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && flag == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (flag == false)
		philo_print_state(philo, STATUS_THINK);
	nonblock_sleep(table, time_to_think);
}
