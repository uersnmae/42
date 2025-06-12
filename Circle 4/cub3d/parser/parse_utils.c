/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:57:25 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/10 09:50:55 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "parser.h"
#include "utils.h"

#define VALID_MAP_CHARS	"01 NSEW"

int	is_valid_map_char(char c)
{
	return (ft_strchr(VALID_MAP_CHARS, c) != NULL);
}

int	set_player_spawn(t_config *cfg, int x, int y, char dir)
{
	if (cfg->player_dir)
		return (error_status(0, 0, "Error: multiple player spawns"));
	cfg->player_x = x + 0.5;
	cfg->player_y = y + 0.5;
	cfg->player_dir = dir;
	return (0);
}

int	is_map_line(const char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	return (*line == '1');
}

int	validate_cfg(t_config *cfg)
{
	if (!cfg->tex_no || !cfg->tex_so || !cfg->tex_we || !cfg->tex_ea)
	{
		free_cfg(cfg);
		return (error_status(EXIT_FAILURE, 0,
				"Error: missing texture file path"));
	}
	if (cfg->floor_rgb[0] == cfg->floor_rgb[1]
		&& cfg->floor_rgb[1] == cfg->floor_rgb[2] && cfg->floor_rgb[0] == -1)
	{
		free_cfg(cfg);
		return (error_status(EXIT_FAILURE, 0,
				"Error: missing floor color data"));
	}
	if (cfg->ceil_rgb[0] == cfg->ceil_rgb[1]
		&& cfg->ceil_rgb[1] == cfg->ceil_rgb[2] && cfg->ceil_rgb[0] == -1)
	{
		free_cfg(cfg);
		return (error_status(EXIT_FAILURE, 0,
				"Error: missing ceiling color data"));
	}
	return (0);
}

void	free_cfg(t_config *cfg)
{
	int	i;

	if (!cfg)
		return ;
	if (cfg->tex_no)
		free(cfg->tex_no);
	if (cfg->tex_so)
		free(cfg->tex_so);
	if (cfg->tex_we)
		free(cfg->tex_we);
	if (cfg->tex_ea)
		free(cfg->tex_ea);
	if (cfg->tex_sprite)
		free(cfg->tex_sprite);
	if (cfg->map)
	{
		i = 0;
		while (i < cfg->map_height)
			if (cfg->map[i])
				free(cfg->map[i++]);
		free(cfg->map);
	}
	ft_memset(cfg, 0, sizeof(t_config));
	free(cfg);
}
