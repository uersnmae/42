/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:20:07 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/21 15:40:47 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line.h"

static void	read_line(t_pipex *data, int pipefd[2], char *buf, char *limiter);

void	here_doc(t_pipex *data, char *limiter)
{
	int		pipefd[2];
	char	*buf;

	if (pipe(pipefd) == -1)
		error(data);
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			error(data);
		buf = get_next_line(STDIN_FILENO);
		read_line(data, pipefd, buf, limiter);
	}
}

static void	read_line(t_pipex *data, int pipefd[2], char *buf, char *limiter)
{
	size_t	buf_len;

	if (!buf)
		error(data);
	while (buf)
	{
		buf_len = ft_strlen(buf);
		if (ft_strncmp(buf, limiter, buf_len - (buf[buf_len - 1] == '\n')) == 0)
			break ;
		write(pipefd[1], buf, buf_len);
		free(buf);
		buf = get_next_line(STDIN_FILENO);
	}
	free(buf);
	free_data(data);
	exit(EXIT_SUCCESS);
}
