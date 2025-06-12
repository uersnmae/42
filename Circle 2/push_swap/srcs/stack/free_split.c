/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:32:23 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/19 14:09:22 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

int	valid_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		if (!valid_arg(splited[i]))
		{
			free_split(splited);
			write(2, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		++i;
	}
	return (i);
}
