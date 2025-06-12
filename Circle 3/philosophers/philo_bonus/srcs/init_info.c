/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:32:40 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/02 16:11:11 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "philo_bonus.h"
#include "philo_bonus_type.h"

#define NAME_MEAL_SEM	"/meal_sem"

int	init_info(t_table *table, char *argv[])
{
	int		index;

	index = 0;
	while (argv[index] != NULL)
	{
		if (!valid_arg(argv[index]) || is_unsigned_num(argv[index]) != 1)
			return (error_status(STR_ERR_INPUT_DIGIT, argv[index], table));
		table->info[index] = get_num(argv[index]);
		++index;
	}
	if (table->info[INFO_NUMBER_OF_PHILOSOPHERS] < 1 || \
		table->info[INFO_NUMBER_OF_PHILOSOPHERS] >= 250)
		return (error_status(STR_ERR_INPUT_POFLOW, "250", table));
	if (index == 4)
		table->info[index] = -1;
	table->start_time = get_time_in_ms() + \
		table->info[INFO_NUMBER_OF_PHILOSOPHERS] * 20;
	table->philo = malloc(sizeof(t_philo) * \
					table->info[INFO_NUMBER_OF_PHILOSOPHERS]);
	if (!table->philo)
		return (error_status(STR_ERR_MALLOC, NULL, table));
	table->philo_stop = false;
	return (0);
}

int	init_semaphores(t_table *table)
{
	const int	num = table->info[INFO_NUMBER_OF_PHILOSOPHERS];

	sem_unlink("/forks");
	sem_unlink("/monitor_sem");
	sem_unlink("/print_sem");
	sem_unlink("/death_sem");
	sem_unlink("/meal_sem");
	table->forks_sem = sem_open("/forks", O_CREAT, 0644, num);
	if (table->forks_sem == SEM_FAILED)
		return (error_status(STR_ERR_SEMAPHORE, NULL, table));
	table->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	if (table->print_sem == SEM_FAILED)
		return (error_status(STR_ERR_SEMAPHORE, NULL, table));
	table->monitor_sem = sem_open("/monitor_sem", O_CREAT, 0644, 1);
	if (table->monitor_sem == SEM_FAILED)
		return (error_status(STR_ERR_SEMAPHORE, NULL, table));
	table->death_sem = sem_open("/death_sem", O_CREAT, 0644, num);
	if (table->death_sem == SEM_FAILED)
		return (error_status(STR_ERR_SEMAPHORE, NULL, table));
	table->meal_sem = sem_open("/meal_sem", O_CREAT, 0644, num);
	if (table->meal_sem == SEM_FAILED)
		return (error_status(STR_ERR_SEMAPHORE, NULL, table));
	return (0);
}

int	init_philo(t_table *table)
{
	static int	index;

	while (index < table->info[INFO_NUMBER_OF_PHILOSOPHERS])
	{
		table->philo[index].philosopher = fork();
		if (table->philo[index].philosopher == -1)
			return (error_status(STR_ERR_FORK, NULL, table));
		if (table->philo[index].philosopher == 0)
		{
			table->philo[index].table = table;
			table->philo[index].philo_index = index;
			table->philo[index].last_meal = table->start_time;
			table->philo[index].eat_count = 0;
			philo_routine(&table->philo[index]);
			exit(EXIT_SUCCESS);
		}
		index++;
	}
	return (0);
}

int	wait_philo(t_table *table)
{
	sem_unlink("/main_sem");
	table->main_sem = sem_open("/main_sem", O_CREAT, 0644, 1);
	if (table->main_sem == SEM_FAILED)
		return (error_status(STR_ERR_SEMAPHORE, NULL, table));
	if (pthread_create(&table->monitor_main_eatcnt, NULL,
			monitor_main_eatcnt, table) < 0)
		return (1);
	if (pthread_create(&table->monitor_main_death, NULL,
			monitor_main_death, table) < 0)
		return (1);
	while (waitpid(-1, NULL, 0) > 0)
		;
	pthread_join(table->monitor_main_death, NULL);
	pthread_join(table->monitor_main_eatcnt, NULL);
	return (0);
}

char	*get_meal_sem_name(int philo_index)
{
	static char	name[64];
	char		temp[32];
	int			index;
	int			tndex;

	memset(name, '\0', sizeof(name));
	index = -1;
	while (NAME_MEAL_SEM[++index] != '\0')
		name[index] = NAME_MEAL_SEM[index];
	tndex = 0;
	if (philo_index == 0)
		temp[tndex++] = '0';
	else
	{
		while (philo_index > 0)
		{
			temp[tndex++] = (philo_index % 10) + '0';
			philo_index /= 10;
		}
	}
	while (tndex > 0)
		name[index++] = temp[--tndex];
	return (name);
}
