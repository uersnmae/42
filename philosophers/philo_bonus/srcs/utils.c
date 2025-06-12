/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:50:58 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/07 18:20:11 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philo_bonus.h"
#include "philo_bonus_type.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	wait_delay(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		usleep(100);
}

void	nonblock_sleep(t_table *table, time_t duration)
{
	time_t	current;

	(void)table;
	current = get_time_in_ms();
	while (get_time_in_ms() - current < duration)
		usleep(100);
}

void	lone_philo_routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	sem_wait(table->forks_sem);
	philo_print_state(philo, STATUS_PICK_FORK_1);
	nonblock_sleep(table, table->info[INFO_TIME_TO_DIE]);
	sem_post(table->forks_sem);
}
