/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:40:22 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/10 09:49:28 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_parse_key
{
	PARSE_NO,
	PARSE_SO,
	PARSE_WE,
	PARSE_EA,
	PARSE_SPRITE,
	PARSE_FLOOR,
	PARSE_CEILING,
	PARSE_MAP,
	PARSE_UNKNOWN
}	t_parse_key;

typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	char	*tex_sprite;
	int		floor_rgb[3];
	int		ceil_rgb[3];
	char	**map;
	int		map_width;
	int		map_height;
	double	player_x;
	double	player_y;
	char	player_dir;
}	t_config;

typedef int	(*t_parse_fn)(char *line, t_config *cfg, t_parse_key key);

typedef struct s_parse_dispatch
{
	const char	*prefix;
	t_parse_key	key;
	t_parse_fn	fn;
}	t_parse_dispatch;

int		parse_config(const char *filename, t_config *cfg);
int		parse_map(int fd, char *first_line, t_config *cfg);
int		is_map_line(const char *line);

int		dispatch_parse_line(char *line, t_config *cfg);

int		parse_tex(char *line, t_config *cfg, t_parse_key key);
int		parse_rgb(char *line, t_config *cfg, t_parse_key key);

int		validate_map(t_config *cfg);
int		validate_cfg(t_config *cfg);
void	free_cfg(t_config *cfg);

// parse_utils.c
int		is_valid_map_char(char c);
int		set_player_spawn(t_config *cfg, int x, int y, char dir);

#endif
