/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:26:47 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/02 14:09:32 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TYPE_H
# define PHILO_TYPE_H

# include <pthread.h>
# include <stdbool.h>

enum e_info
{
	INFO_NUMBER_OF_PHILOSOPHERS,
	INFO_TIME_TO_DIE,
	INFO_TIME_TO_EAT,
	INFO_TIME_TO_SLEEP,
	INFO_NUMBER_OF_TIMES_EACH_PHILOSOHPER_MUST_EAT
};

enum e_status
{
	STATUS_INIT,
	STATUS_PICK_FORK_1,
	STATUS_PICK_FORK_2,
	STATUS_EAT,
	STATUS_SLEEP,
	STATUS_THINK,
	STATUS_DEAD
};

typedef struct s_philo	t_philo;

typedef struct s_table
{
	pthread_mutex_t	write_lock;
	pthread_mutex_t	monitor_lock;
	pthread_mutex_t	*fork_lock;
	pthread_t		monitor;
	time_t			start_time;
	int				info[5];
	bool			philo_stop;
	t_philo			*philo;
}	t_table;

typedef struct s_philo
{
	pthread_mutex_t	meal_lock;
	pthread_t		philosopher;
	int				philo_index;
	int				fork_index[2];
	int				eat_count;
	time_t			last_meal;
	t_table			*table;
}	t_philo;

#endif
