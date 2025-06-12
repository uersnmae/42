/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:27:50 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/02 16:12:23 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# include "philo_bonus_type.h"

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
# define STR_ERR_FORK			"%s error: Could not create process.\n"
# define STR_ERR_MALLOC			"%s error: Could not allocate memory.\n"
# define STR_ERR_SEMAPHORE		"%s error: Could not create semaphore\n"
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

int		init_info(t_table *table, char *argv[]);
int		init_semaphores(t_table *table);
int		init_philo(t_table *table);
int		wait_philo(t_table *table);
char	*get_meal_sem_name(int philo_index);

int		is_unsigned_num(char *str);
int		get_num(char *str);
bool	valid_arg(char *arg);

time_t	get_time_in_ms(void);
void	wait_delay(time_t start_time);
void	nonblock_sleep(t_table *table, time_t duration);
void	lone_philo_routine(t_philo *philo);

void	philo_routine(t_philo *philo);

int		philo_print_state(const t_philo *philo, enum e_status status);

int		error_status(char *str, char *detail, t_table *table);
void	destroy_sem(t_table *table);
int		put_msg(char *str, char *detail, int err_no);
void	free_table(t_table *table);

void	kill_all(t_table *table);
void	*monitor_philo(void *data);

void	set_philo_stop(t_table *table, bool value);
void	*monitor_main_death(void *data);
void	*monitor_main_eatcnt(void *data);

#endif
