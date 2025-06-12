/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:03:35 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/10 09:58:56 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "parser.h"
#include "utils.h"

typedef struct s_mapinfo
{
	char	**map;
	char	**visited;
	int		width;
	int		height;
}	t_mapinfo;

static int	is_walkable(char c)
{
	return (c == '0' || ft_strchr("NSEW", c));
}

static int	flood_fill(t_mapinfo *info, int y, int x)
{
	if (y < 0 || x < 0 || y >= info->height || x >= info->width)
		return (0);
	if (info->visited[y][x] || info->map[y][x] == ' ')
		return (info->map[y][x] != ' ');
	if (!is_walkable(info->map[y][x]))
		return (1);
	info->visited[y][x] = 1;
	if (!flood_fill(info, y + 1, x))
		return (0);
	if (!flood_fill(info, y - 1, x))
		return (0);
	if (!flood_fill(info, y, x + 1))
		return (0);
	if (!flood_fill(info, y, x - 1))
		return (0);
	return (1);
}

static char	**alloc_visited(int h, int w)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * h);
	i = 0;
	while (i < h)
	{
		visited[i] = ft_calloc(w, sizeof(char));
		if (!visited[i])
			exit(EXIT_FAILURE);
		i++;
	}
	return (visited);
}

static void	free_visited(char **visited, int h)
{
	int	i;

	i = 0;
	while (i < h)
		free(visited[i++]);
	free(visited);
}

int	validate_map(t_config *cfg)
{
	t_mapinfo	info;
	int			y;
	int			x;

	if (cfg->player_dir == 0)
	{
		free_cfg(cfg);
		return (error_status(0, 0,
				"Error: No player start position found in map"));
	}
	y = (int)cfg->player_y;
	x = (int)cfg->player_x;
	info.map = cfg->map;
	info.height = cfg->map_height;
	info.width = cfg->map_width;
	info.visited = alloc_visited(info.height, info.width);
	if (!flood_fill(&info, y, x))
	{
		free_cfg(cfg);
		ft_putendl_fd("Error: Map is not enclosed", STDERR_FILENO);
		free_visited(info.visited, info.height);
		exit(EXIT_FAILURE);
	}
	free_visited(info.visited, info.height);
	return (0);
}
