/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:14:52 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/10 08:51:36 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>

#include "get_next_line/get_next_line.h"
#include "libft.h"
#include "parser.h"
#include "utils.h"

#define LINE	0
#define TRIM	1

static void	chomp_newline(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
		if (len > 1 && str[len - 2] == '\r')
			str[len - 2] = '\0';
	}
}

static int	get_parsed_map(int fd, char *raw_line, t_config *cfg)
{
	int	ret;

	chomp_newline(raw_line);
	ret = parse_map(fd, raw_line, cfg);
	if (ret)
	{
		free_cfg(cfg);
		return (ret);
	}
	return (ret);
}

static int	parse_line_and_dispatch(int fd, char *raw_line, t_config *cfg)
{
	char	*trimmed_line;
	int		is_map_line_flag;

	trimmed_line = ft_strtrim(raw_line, " \t\r\n");
	if (!trimmed_line || trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (0);
	}
	is_map_line_flag = is_map_line(trimmed_line);
	if (is_map_line_flag)
	{
		free(trimmed_line);
		if (get_parsed_map(fd, raw_line, cfg))
			return (1);
		return (2);
	}
	if (dispatch_parse_line(trimmed_line, cfg) != 0)
	{
		free(trimmed_line);
		return (1);
	}
	free(trimmed_line);
	return (0);
}

int	parse_config(const char *filename, t_config *cfg)
{
	const int	fd = open(filename, O_RDONLY);
	char		*raw_line;
	static int	status;

	if (fd < 0)
	{
		free_cfg(cfg);
		return (error_status(0, errno, "Error: Invalid file descriptor\n"));
	}
	ft_memset(cfg->floor_rgb, -1, sizeof(int) * 3);
	ft_memset(cfg->ceil_rgb, -1, sizeof(int) * 3);
	while (get_next_line_ez(&raw_line, fd) && status != 2)
	{
		status = parse_line_and_dispatch(fd, raw_line, cfg);
		free(raw_line);
		if (status == 1)
		{
			close(fd);
			return (1);
		}
	}
	close(fd);
	if (validate_cfg(cfg) || validate_map(cfg))
		return (1);
	return (0);
}
