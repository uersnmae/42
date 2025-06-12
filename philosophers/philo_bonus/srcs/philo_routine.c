/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:51:08 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/30 19:30:55 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "philo_bonus.h"
#include "philo_bonus_type.h"

static void	philo_eat_and_sleep(t_philo *philo, t_table *table);
static void	philo_think(t_philo *philo, t_table *table, bool flag);

void	philo_routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	sem_wait(table->death_sem);
	sem_wait(table->meal_sem);
	if (pthread_create(&philo->philo_monitor, NULL, \
					monitor_philo, philo) != 0)
		return ((void)error_status(STR_ERR_THREAD, NULL, table));
	wait_delay(table->start_time);
	if (table->info[INFO_NUMBER_OF_PHILOSOPHERS] == 1)
	{
		lone_philo_routine(philo);
		return ;
	}
	if (philo->philo_index % 2 == 1)
		philo_think(philo, table, true);
	while (true)
	{
		philo_eat_and_sleep(philo, table);
		philo_think(philo, table, false);
	}
	pthread_join(philo->philo_monitor, NULL);
}

static void	philo_eat_and_sleep(t_philo *philo, t_table *table)
{
	sem_wait(table->forks_sem);
	philo_print_state(philo, STATUS_PICK_FORK_1);
	sem_wait(table->forks_sem);
	philo_print_state(philo, STATUS_PICK_FORK_2);
	philo_print_state(philo, STATUS_EAT);
	sem_wait(table->monitor_sem);
	philo->last_meal = get_time_in_ms();
	sem_post(table->monitor_sem);
	nonblock_sleep(table, table->info[INFO_TIME_TO_EAT]);
	sem_wait(table->monitor_sem);
	philo->eat_count++;
	sem_post(table->monitor_sem);
	sem_post(table->forks_sem);
	sem_post(table->forks_sem);
	philo_print_state(philo, STATUS_SLEEP);
	nonblock_sleep(table, table->info[INFO_TIME_TO_SLEEP]);
}

static void	philo_think(t_philo *philo, t_table *table, bool flag)
{
	time_t	time_to_think;

	sem_wait(table->monitor_sem);
	time_to_think = (table->info[INFO_TIME_TO_DIE] \
					- (get_time_in_ms() - philo->last_meal) \
					- table->info[INFO_TIME_TO_EAT]) / 2;
	sem_post(table->monitor_sem);
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
