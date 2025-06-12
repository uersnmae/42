/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:42:48 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/24 10:44:32 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line_ez(char **buf, int fd)
{
	*buf = get_next_line(fd);
	if (*buf != NULL)
		return (1);
	else
		return (0);
}
