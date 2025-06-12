/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:42:49 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/02 16:12:21 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

# include "philo_type.h"

/*
 * ERROR MASSAGES
 */
# define STR_PROG_NAME			"philo"
# define STR_ERR_USAGE			"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"%s invalied input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW	"%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define STR_ERR_THREAD			"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC			"%s error: Could not allocate memory.\n"
# define STR_ERR_MUTEX			"%s error: Could not create mutex\n"
# define STR_ERR_MUTEX_LOCK		"%s error: Could not lock mutex\n"
# define STR_ERR_MUTEX_UNLOCK	"%s error: Could not unlock mutex\n"
# define STR_ERR_PRINT_STATE	"%s error: Could not print state\n"
# define STR_ERR_WRITE_STATE	"%s error: Could not write state\n"

/*
* STATE MASSAGES
 */
# define STR_STATE_TAKE_FORK	"%ld %d has taken a fork\n"
# define STR_STATE_EAT			"%ld %d is eating\n"
# define STR_STATE_SLEEP		"%ld %d is sleeping\n"
# define STR_STATE_THINK		"%ld %d is thinking\n"
# define STR_STATE_DEAD			"%ld %d died\n"

void	*philo_routine(void *data);
void	nonblock_sleep(t_table *table, time_t duration);
void	*lone_philo_routine(t_philo *philo);

int		init_info(t_table *table, char *argv[]);
int		init_mutex(t_table *table);
int		init_philo(t_table *table);
int		join_philo(t_table *table);

int		error_status(char *str, char *detail, t_table *table);

void	*monitor_routine(void *data);
bool	is_philo_stop(t_table *table);

time_t	get_time_in_ms(void);
void	get_fork_index(t_philo *philo);
void	wait_delay(time_t start_time);

int		philo_print_state(t_philo *philo, enum e_status status);

bool	valid_arg(char *arg);
int		get_num(char *str);

void	free_table(t_table *table);

bool	valid_arg(char *arg);
int		is_unsigned_num(char *str);
int		is_dead(t_table *table);

#endif
