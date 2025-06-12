/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:14:18 by dong-hki          #+#    #+#             */
/*   Updated: 2025/04/02 17:31:15 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	free_table(t_table *table)
{
	int	index;

	if (table == NULL)
		return ;
	if (table->fork_lock != NULL)
	{
		index = 0;
		while (index < table->info[INFO_NUMBER_OF_PHILOSOPHERS])
			pthread_mutex_destroy(&table->fork_lock[index++]);
		free(table->fork_lock);
		pthread_mutex_destroy(&table->write_lock);
	}
	if (table->philo != NULL)
		free(table->philo);
	free(table);
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
