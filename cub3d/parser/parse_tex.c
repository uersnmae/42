/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:56:35 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/10 09:56:27 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int	parse_tex(char *line, t_config *cfg, t_parse_key key)
{
	char		*path;

	path = ft_strtrim(line, " \t\n");
	if (!path)
		return (1);
	if (key == PARSE_NO && cfg->tex_no == NULL)
		cfg->tex_no = path;
	else if (key == PARSE_SO && cfg->tex_so == NULL)
		cfg->tex_so = path;
	else if (key == PARSE_WE && cfg->tex_we == NULL)
		cfg->tex_we = path;
	else if (key == PARSE_EA && cfg->tex_ea == NULL)
		cfg->tex_ea = path;
	else if (key == PARSE_SPRITE && cfg->tex_sprite == NULL)
		cfg->tex_sprite = path;
	else
	{
		free(path);
		return (1);
	}
	return (0);
}
