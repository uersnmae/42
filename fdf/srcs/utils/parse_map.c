/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:59:22 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/03 18:03:32 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "fdf.h"
#include "get_next_line.h"

static int	get_width(t_fdf *fdf, char *filename);
static int	get_height(t_fdf *fdf, char *filename);
static void	fill_grid(t_fdf *fdf, int **grid, char *buf, int width);
static void	get_z_range(t_map *map);

void	check_map(t_fdf *fdf, char *filename, t_map *map)
{
	int		fd;
	int		i;
	char	*buf;

	map->width = get_width(fdf, filename);
	map->height = get_height(fdf, filename);
	map->grid = malloc(sizeof(int **) * map->height);
	if (!map->grid)
		error_return(fdf, "mallocating map->grid error", NON_SYS);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_return(fdf, "open error in check_map()", SYS);
	i = -1;
	while (get_next_line_ez(&buf, fd) && *buf != '\0')
	{
		map->grid[++i] = malloc((sizeof(int *) * map->width));
		if (!map->grid[i])
			error_return(fdf, "mallocating map->grid[i] error", NON_SYS);
		fill_grid(fdf, map->grid[i], buf, map->width);
	}
	close(fd);
	get_z_range(map);
}

static void	fill_grid(t_fdf *fdf, int **grid, char *buf, int width)
{
	char	**split;
	int		i;
	int		j;

	split = ft_split(buf, ' ');
	free(buf);
	i = -1;
	while (split[++i] && i < width)
	{
		grid[i] = malloc(sizeof(int) * 2);
		if (!grid[i])
			error_split(fdf, "malloc failed. (fill_grid)", split, i);
		grid[i][0] = ft_atoi(split[i]);
		j = 0;
		while (split[i][j] && split[i][j] != ',')
			++j;
		if (split[i][j] == ',')
			grid[i][1] = ft_atoi_base(&split[i][j + 1], HEX_BASE);
		else
			grid[i][1] = -1;
		free(split[i]);
	}
	if (i != width || split[i])
		error_split(fdf, "invalid map file", split, i);
	free(split);
}

static void	get_z_range(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->z_min = map->grid[0][0][0];
	map->z_max = map->grid[0][0][0];
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j][0] < map->z_min)
				map->z_min = map->grid[i][j][0];
			if (map->grid[i][j][0] > map->z_max)
				map->z_max = map->grid[i][j][0];
			++j;
		}
		++i;
	}
}

static int	get_width(t_fdf *fdf, char *filename)
{
	int		fd;
	int		i;
	int		width;
	char	*buf;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_return(fdf, "Open Error!!", SYS);
	width = 0;
	get_next_line_ez(&buf, fd);
	if (*buf == '\0')
		error_return(fdf, "Empty file!", SYS);
	i = -1;
	while (buf[++i])
		if (buf[i] != ' ' && (buf[i + 1] == ' ' || buf[i + 1] == '\0'))
			++width;
	free(buf);
	while (get_next_line_ez(&buf, fd))
		free(buf);
	free(buf);
	close(fd);
	return (width);
}

static int	get_height(t_fdf *fdf, char *filename)
{
	int		fd;
	int		height;
	char	*buf;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_return(fdf, "Open Error!!", SYS);
	height = 0;
	while (get_next_line_ez(&buf, fd) && *buf != '\0')
	{
		++height;
		free(buf);
	}
	free(buf);
	close(fd);
	return (height);
}
