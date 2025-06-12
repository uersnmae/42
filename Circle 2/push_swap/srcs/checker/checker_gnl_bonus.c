/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_gnl_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:17:03 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/21 11:06:20 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"
#include "get_next_line.h"

static char	*ps_substr(char **buf, size_t index)
{
	char	*temp;
	char	*line;
	int		buf_len;

	buf_len = gnl_strlen(*buf);
	line = gnl_substr(*buf, 0, index);
	temp = *buf;
	*buf = gnl_substr(*buf, index, buf_len - index);
	free(temp);
	if (string_to_op(line) == null_op)
		free(*buf);
	return (line);
}

char	*get_next_line_ps(int fd)
{
	static char	*buf;
	char		*line;
	size_t		index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = gnl_read_file(fd, buf);
	if (buf == NULL || *buf == '\0')
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	index = 0;
	while (*(buf + index) && *(buf + index) != '\n')
		index++;
	if (*(buf + index) == '\n')
		index++;
	line = ps_substr(&buf, index);
	return (line);
}
