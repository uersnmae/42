/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dispatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:56:10 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/10 08:57:34 by hakslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "parser.h"

static const t_parse_dispatch	g_parse_table[] = {
{"NO", PARSE_NO, parse_tex},
{"SO", PARSE_SO, parse_tex},
{"WE", PARSE_WE, parse_tex},
{"EA", PARSE_EA, parse_tex},
{"SP", PARSE_SPRITE, parse_tex},
{"F", PARSE_FLOOR, parse_rgb},
{"C", PARSE_CEILING, parse_rgb},
{NULL, PARSE_UNKNOWN, NULL}
};

static const t_parse_dispatch	*find_dispatch_entry(char *line)
{
	size_t	i;
	size_t	prefix_len;

	i = 0;
	while (g_parse_table[i].prefix)
	{
		prefix_len = ft_strlen(g_parse_table[i].prefix);
		if (ft_strncmp(line, g_parse_table[i].prefix, prefix_len) == 0
			&& ft_isspace(line[prefix_len]))
			return (&g_parse_table[i]);
		i++;
	}
	return (NULL);
}

static char	*skip_prefix_whitespace(char *line, const char *prefix)
{
	size_t	i;

	i = ft_strlen(prefix);
	while (ft_isspace(line[i]))
		i++;
	return (line + i);
}

int	dispatch_parse_line(char *line, t_config *cfg)
{
	const t_parse_dispatch	*entry = find_dispatch_entry(line);
	char					*arg;

	if (!entry)
	{
		ft_putstr_fd("Error: unknown config line: ", STDERR_FILENO);
		ft_putendl_fd(line, STDERR_FILENO);
		free_cfg(cfg);
		return (1);
	}
	arg = skip_prefix_whitespace(line, entry->prefix);
	if (entry->fn(arg, cfg, entry->key) != 0)
	{
		free_cfg(cfg);
		return (1);
	}
	return (0);
}
