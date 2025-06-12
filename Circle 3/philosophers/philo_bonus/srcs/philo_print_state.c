/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:25:40 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/08 10:27:33 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

#include "philo_bonus.h"

int	philo_print_state(const t_philo *philo, enum e_status status)
{
	time_t	current_time;
	time_t	timestamp;

	sem_wait(philo->table->print_sem);
	current_time = get_time_in_ms();
	timestamp = current_time - philo->table->start_time;
	if (status == STATUS_PICK_FORK_1 || status == STATUS_PICK_FORK_2)
		printf(STR_STATE_TAKE_FORK, timestamp, philo->philo_index + 1);
	else if (status == STATUS_EAT)
		printf(STR_STATE_EAT, timestamp, philo->philo_index + 1);
	else if (status == STATUS_SLEEP)
		printf(STR_STATE_SLEEP, timestamp, philo->philo_index + 1);
	else if (status == STATUS_THINK)
		printf(STR_STATE_THINK, timestamp, philo->philo_index + 1);
	else if (status == STATUS_DEAD)
		printf(STR_STATE_DEAD, timestamp, philo->philo_index + 1);
	sem_post(philo->table->print_sem);
	return (0);
}
