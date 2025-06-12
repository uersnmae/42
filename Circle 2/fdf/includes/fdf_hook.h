/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:56:30 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/02 15:33:25 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_HOOK_H
# define FDF_HOOK_H

# define SHIFT_L		65505
# define SHIFT_R		65506

# define ARROW_LEFT		65361
# define ARROW_UP		65362
# define ARROW_RIGHT	65363
# define ARROW_DOWN		65364

# define KEY_W			119
# define KEY_S			115
# define KEY_A			97
# define KEY_D			100
# define KEY_R			114
# define KEY_T			116
# define PLUS			61
# define MINUS			45
# define ESC			0xFF1B

# include "fdf.h"

// hook_arrow.c
int		hook_rotate(int keycode, t_fdf *fdf);

// hook_key.c
void	hook_translate(int keycode, t_fdf *fdf);
void	hook_reset(t_fdf *fdf);
void	hook_toggle_view(t_fdf *fdf);

// hook_key.c
void	offset_up(t_fdf *fdf);
void	offset_down(t_fdf *fdf);
void	offset_left(t_fdf *fdf);
void	offset_right(t_fdf *fdf);

// hook_mouse.c
void	scroll_down(t_fdf *fdf);
void	scroll_up(t_fdf *fdf);

#endif
