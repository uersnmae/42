/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:30:01 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/31 16:28:49 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>

#include "philo_bonus.h"

static time_t	get_last_meal_time(t_philo *philo);
static int		get_eat_count(t_philo *philo);

void	kill_all(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->info[INFO_NUMBER_OF_PHILOSOPHERS])
	{
		if (kill(table->philo[index].philosopher, SIGKILL) != 0)
			return ;
		index++;
	}
}

void	*monitor_philo(void *data)
{
	static bool	posted = false;
	t_philo		*philo;
	t_table		*table;
	int			num;

	philo = (t_philo *)data;
	table = philo->table;
	num = table->info[INFO_NUMBER_OF_TIMES_EACH_PHILOSOHPER_MUST_EAT];
	while (true)
	{
		if (get_time_in_ms() - get_last_meal_time(philo) >= \
			table->info[INFO_TIME_TO_DIE] && !posted)
		{
			philo_print_state(philo, STATUS_DEAD);
			sem_post(table->death_sem);
			posted = true;
		}
		if (num != -1 && !posted && get_eat_count(philo) == num)
		{
			sem_post(table->meal_sem);
			posted = true;
		}
		usleep(100);
	}
	return (NULL);
}

static time_t	get_last_meal_time(t_philo *philo)
{
	time_t	last_meal_time;

	sem_wait(philo->table->monitor_sem);
	last_meal_time = philo->last_meal;
	sem_post(philo->table->monitor_sem);
	return (last_meal_time);
}

static int	get_eat_count(t_philo *philo)
{
	int	count;

	sem_wait(philo->table->monitor_sem);
	count = philo->eat_count;
	sem_post(philo->table->monitor_sem);
	return (count);
}
