/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_type.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:17:03 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/30 19:41:06 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_TYPE_H
# define PHILO_BONUS_TYPE_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>

# define EXIT_PHILO_DEAD	1
# define EXIT_PHILO_FULL	-1

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
	pthread_t	monitor_main_death;
	pthread_t	monitor_main_eatcnt;
	time_t		start_time;
	sem_t		*print_sem;
	sem_t		*monitor_sem;
	sem_t		*forks_sem;
	sem_t		*death_sem;
	sem_t		*meal_sem;
	sem_t		*main_sem;
	bool		philo_stop;
	int			info[5];
	t_philo		*philo;
}	t_table;

typedef struct s_philo
{
	pthread_t	philo_monitor;
	time_t		last_meal;
	pid_t		philosopher;
	int			philo_index;
	int			eat_count;
	t_table		*table;
}	t_philo;

#endif
