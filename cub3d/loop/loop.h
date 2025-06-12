/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 11:58:19 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/08 12:18:32 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_H
# define LOOP_H

# include <sys/time.h>

# define SHIFT_L		65505
# define SHIFT_R		65506

# define KEY_LEFT		65361
# define KEY_UP			65362
# define KEY_RIGHT		65363
# define KEY_DOWN		65364

# define KEY_W			119
# define KEY_S			115
# define KEY_A			97
# define KEY_D			100
# define KEY_R			114
# define KEY_T			116
# define KEY_PLUS		61
# define KEY_MINUS		45
# define KEY_ESC		0xFF1B

# include "game.h"

void	init_hooks(t_game *game);
int		init_mlx(t_game *game);
int		main_loop(t_game *game);

double	get_delta_time(struct timeval *start_time);
void	limit_frame_sleep(struct timeval *start_time);

#endif
