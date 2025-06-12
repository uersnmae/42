/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:47:49 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/08 11:38:42 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libft.h"

void	free_split(char **argv)
{
	size_t	i;

	if (!argv || !*argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

int	error_status(int status, int errnum, char *format)
{
	if (errnum)
	{
		ft_putstr_fd(format, STDERR_FILENO);
		ft_putendl_fd(strerror(errnum), STDERR_FILENO);
	}
	else
		ft_putendl_fd(format, STDERR_FILENO);
	if (status)
		exit(status);
	else
		return (-1);
}
