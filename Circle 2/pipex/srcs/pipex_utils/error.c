/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:18:41 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/14 15:54:55 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(t_pipex *data)
{
	ft_putendl_fd("Error!!\n", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	free_data(data);
	exit(EXIT_FAILURE);
}
