/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:32:31 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/31 16:26:51 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>

#include "philo_bonus.h"
#include "philo_bonus_type.h"

void	set_philo_stop(t_table *table, bool value)
{
	sem_wait(table->main_sem);
	table->philo_stop = value;
	sem_post(table->main_sem);
}

static bool	get_philo_stop(t_table *table)
{
	bool	value;

	sem_wait(table->main_sem);
	value = table->philo_stop;
	sem_post(table->main_sem);
	return (value);
}

void	*monitor_main_death(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	sem_wait(table->death_sem);
	kill_all(table);
	set_philo_stop(table, true);
	sem_post(table->meal_sem);
	return (NULL);
}

void	*monitor_main_eatcnt(void *data)
{
	t_table	*table;
	int		cnt;

	table = (t_table *)data;
	cnt = 0;
	while (get_philo_stop(table) == false
		&& cnt != table->info[INFO_NUMBER_OF_PHILOSOPHERS])
	{
		if (sem_wait(table->meal_sem) == 0)
			cnt++;
	}
	kill_all(table);
	set_philo_stop(table, true);
	sem_post(table->death_sem);
	return (NULL);
}
