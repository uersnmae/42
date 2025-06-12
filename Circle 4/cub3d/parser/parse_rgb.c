/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:39:46 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/10 08:51:23 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "parser.h"
#include "utils.h"

static int	parse_component(char *str)
{
	int	val;
	int	i;

	if (!str || *str == '\0')
		return (-1);
	i = 0;
	while (str[i])
		if (ft_isdigit(str[i++]) == 0)
			return (-1);
	val = ft_atoi(str);
	if (val < 0 || val > 255)
		return (-1);
	return (val);
}

static int	validate_and_parse_rgb(char **split, int rgb[3])
{
	int	i;
	int	val;

	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (error_status(0, 0,
				"Error: RGB must be 3 comma-separated values"));
	i = 0;
	while (i < 3)
	{
		val = parse_component(split[i]);
		if (val == -1)
		{
			return (error_status(0, 0,
					"Error: RGB value must be 0~255 integer"));
		}
		rgb[i] = val;
		i++;
	}
	return (0);
}

static int	store_rgb_to_config(t_config *cfg, t_parse_key key, int rgb[3])
{
	if (key == PARSE_FLOOR && (cfg->floor_rgb[0] == -1
			&& cfg->floor_rgb[1] == -1 && cfg->floor_rgb[2] == -1))
		ft_memcpy(cfg->floor_rgb, rgb, sizeof(int) * 3);
	else if (key == PARSE_CEILING && (cfg->ceil_rgb[0] == -1
			&& cfg->ceil_rgb[1] == -1 && cfg->ceil_rgb[2] == -1))
		ft_memcpy(cfg->ceil_rgb, rgb, sizeof(int) * 3);
	else
	{
		ft_putendl_fd("Error: RGB called with invalid key", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	parse_rgb(char *line, t_config *cfg, t_parse_key key)
{
	char	**split;
	int		rgb[3];

	split = ft_split(line, ',');
	if (validate_and_parse_rgb(split, rgb)
		|| store_rgb_to_config(cfg, key, rgb))
	{
		free_split(split);
		return (1);
	}
	free_split(split);
	return (0);
}
