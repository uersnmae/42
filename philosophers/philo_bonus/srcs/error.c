/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:14:18 by dong-hki          #+#    #+#             */
/*   Updated: 2025/05/30 19:42:41 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "philo_bonus.h"
#include "philo_bonus_type.h"

void	free_table(t_table *table)
{
	if (table == NULL)
		return ;
	destroy_sem(table);
	free(table->philo);
	free(table);
}

void	destroy_sem(t_table *table)
{
	sem_close(table->forks_sem);
	sem_unlink("/forks");
	sem_close(table->print_sem);
	sem_unlink("/print_sem");
	sem_close(table->monitor_sem);
	sem_unlink("/monitor_sem");
	sem_close(table->death_sem);
	sem_unlink("/death_sem");
	sem_close(table->meal_sem);
	sem_unlink("/meal_sem");
	sem_close(table->main_sem);
	sem_unlink("/main_sem");
}

int	put_msg(char *str, char *detail, int err_no)
{
	if (detail == NULL)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (err_no);
}

int	error_status(char *str, char *detail, t_table *table)
{
	if (table != NULL)
		free_table(table);
	put_msg(str, detail, EXIT_FAILURE);
	return (1);
}
