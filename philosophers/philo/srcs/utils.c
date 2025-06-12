/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:32:37 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/05 15:58:35 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	get_fork_index(t_philo *philo)
{
	int	num;

	num = philo->table->info[INFO_NUMBER_OF_PHILOSOPHERS];
	philo->fork_index[0] = philo->philo_index;
	philo->fork_index[1] = (philo->philo_index + 1) % num;
	if (philo->philo_index % 2 == 1)
	{
		philo->fork_index[0] = (philo->philo_index + 1) % num;
		philo->fork_index[1] = philo->philo_index;
	}
}

void	wait_delay(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		usleep(100);
}

void	nonblock_sleep(t_table *table, time_t duration)
{
	time_t	current;

	current = get_time_in_ms();
	while (get_time_in_ms() - current < duration)
	{
		if (is_philo_stop(table) == true)
			return ;
		usleep(100);
	}
}

void	*lone_philo_routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->fork_lock[philo->fork_index[0]]);
	philo_print_state(philo, STATUS_PICK_FORK_1);
	pthread_mutex_unlock(&table->fork_lock[philo->fork_index[0]]);
	return (NULL);
}
