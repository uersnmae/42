/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:04:00 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 10:51:02 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdbool.h>
# include <stddef.h>

# include "parser.h"

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

# define TEX_COUNT	5

typedef enum e_tex_index
{
	TEX_NORTH = 0,
	TEX_SOUTH,
	TEX_WEST,
	TEX_EAST,
	TEX_SPRITE
}	t_tex_index;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*data_addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			img_w;
	int			img_h;
}	t_mlx;

typedef struct s_tex
{
	void	*img;
	char	*data_addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex;

typedef struct s_game
{
	t_config		*cfg;
	char			**map;
	int				map_rows;
	int				map_cols;
	double			player_x;
	double			player_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			delta_time;
	int				screen_w;
	int				screen_h;
	unsigned int	floor_color;
	unsigned int	ceil_color;
	double			*z_buffer;
	t_mlx			*mlx_wrap;
	t_tex			*tex;
	bool			move_forward;
	bool			move_backward;
	bool			move_left;
	bool			move_right;
	bool			turn_left;
	bool			turn_right;
	bool			should_exit;
	int				mouse_x;
}	t_game;

void	draw_background(t_game *g);

// game_init.c
t_game	*init_game_context(t_config *cfg);
void	free_game_tex(t_game *game);
void	free_game(t_game *game);

// init_mlx.c
int		load_all_textures(t_game *game);
void	unload_all_textures(t_game *game);

// hooks.c
int		main_loop(t_game *game);
void	update_player_state(t_game *game);

void	rotate_player(t_game *game, double rot_direction);
void	init_player_direction(t_game *game);
void	copy_map_from_config(t_game *game);
int		init_mlx(t_game *game);
void	init_hooks(t_game *game);

void	print_map_for_debug(t_game *game);
int		exit_game(t_game *game);

#endif
