/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:48:57 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/24 10:50:54 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft.h"
#include "fdf.h"

void	error_return(t_fdf *fdf, char *str, bool syscall)
{
	if (syscall)
		perror(str);
	else
		ft_putendl_fd(str, STDERR_FILENO);
	if (fdf)
		exit_program(fdf);
	exit(EXIT_FAILURE);
}

void	error_split(t_fdf *fdf, char *str, char **split, int i)
{
	ft_putendl_fd(str, STDERR_FILENO);
	if (split)
	{
		while (split[i])
			free(split[i++]);
		free(split);
	}
	if (fdf)
		exit_program(fdf);
}
