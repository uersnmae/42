/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:16:58 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/10 09:52:45 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "get_next_line/get_next_line.h"
#include "libft.h"
#include "parser.h"
#include "utils.h"

#define MAX_MAP_HEIGHT	512
#define Y				0
#define X				1

static void	chomp_newline(char *str)
{
	size_t	len;

	if (str == NULL)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
		if (len > 1 && str[len - 2] == '\r')
			str[len - 2] = '\0';
	}
}

static char	**collect_map_lines(int fd, char *first, int *out_height)
{
	static size_t	i;
	char			**lines;
	char			*line;

	lines = ft_calloc(MAX_MAP_HEIGHT + 2, sizeof(char *));
	if (!lines)
		return (NULL);
	lines[i++] = ft_strdup(first);
	if (!lines[i - 1])
		exit (EXIT_FAILURE);
	while (get_next_line_ez(&line, fd))
	{
		chomp_newline(line);
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		lines[i++] = line;
		if (i > MAX_MAP_HEIGHT)
			exit(EXIT_FAILURE);
	}
	*out_height = i;
	return (lines);
}

static int	analyze_map(char **lines, int height, t_config *cfg, int *out_width)
{
	char	c;
	int		max_w;
	int		len;
	int		grid[2];

	max_w = 0;
	grid[Y] = -1;
	while (++grid[Y] < height)
	{
		len = ft_strlen(lines[grid[Y]]);
		if (len > max_w)
			max_w = len;
		grid[X] = -1;
		while (++grid[X] < len)
		{
			c = lines[grid[Y]][grid[X]];
			if (!is_valid_map_char(c))
				return (error_status(0, 0, "Error: invalid map character"));
			if (ft_strchr("NSEW", c))
				if (set_player_spawn(cfg, grid[X], grid[Y], c))
					return (1);
		}
	}
	*out_width = max_w;
	return (0);
}

static void	store_map_to_config(
			t_config *cfg,
			char **lines,
			int height,
			int width)
{
	int	y;

	cfg->map = malloc(sizeof(char *) * (height + 1));
	if (!cfg->map)
		exit(EXIT_FAILURE);
	y = 0;
	while (y < height)
	{
		cfg->map[y] = malloc(width + 1);
		if (!cfg->map[y])
			exit(EXIT_FAILURE);
		ft_memset(cfg->map[y], ' ', width);
		ft_memcpy(cfg->map[y], lines[y], ft_strlen(lines[y]));
		cfg->map[y][width] = '\0';
		free(lines[y]);
		y++;
	}
	cfg->map[height] = NULL;
	cfg->map_width = width;
	cfg->map_height = height;
	free(lines);
}

int	parse_map(int fd, char *first_line, t_config *cfg)
{
	char	**lines;
	int		height;
	int		width;

	lines = collect_map_lines(fd, first_line, &height);
	if (analyze_map(lines, height, cfg, &width))
	{
		free_split(lines);
		return (1);
	}
	store_map_to_config(cfg, lines, height, width);
	return (0);
}
