/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:37:19 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/06 12:26:47 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdbool.h>
# include "matrix.h"
# include "map.h"
# include "camera.h"
# include "object.h"

# define PI	3.1415926535897

# define HEX_BASE	"0123456789ABCDEF"

# define WIDTH		1920
# define HEIGHT		1080

# define SYS		true
# define NON_SYS	false

# define MAX_DEPTH	10000000.0

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
	int	reverse;
}	t_point;

typedef struct s_pixel
{
	int		x;
	int		y;
	int		color;
	double	z;
}	t_pixel;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*data_addr;
	int			endian;
	int			bpp;
	int			size_line;
	double		*depth;
	t_object	*object;
	t_camera	*cam;
	t_map		*map;
	t_matrix	final_matrix;
}	t_fdf;

// parse_map.c
void	check_map(t_fdf *fdf, char *filename, t_map *map);

// 
void	wireframe(t_map *map, t_fdf *fdf);

// img_put_pixel.c
void	img_put_pixel(t_fdf *fdf, int x, int y, int color);
void	img_put_pixel_with_depth(t_fdf *fdf, t_pixel pixel);
double	*init_depth(t_fdf *fdf);

// img_put_bresenham_line.c
void	draw_line_bresenham(t_fdf *fdf, t_point start, t_point end);

// projection.c
t_point	project(t_fdf *fdf, int x, int y);

void	error_return(t_fdf *fdf, char *str, bool syscall);
void	error_split(t_fdf *fdf, char *str, char **split, int i);

// algebra.c
double	get_radian(double num);
int		get_min(int x, int y);

// hook_init.c
void	init_hook(t_fdf *fdf);

// mouse_handler.c
int		mouse_handler(int keycode, int x, int y, t_fdf *fdf);

// key_release_handler.c
int		key_release_handler(int keycode, t_fdf *fdf);
int		key_press_handler(int keycode, t_fdf *fdf);
int		exit_program(t_fdf *fdf);

// utils.c
int		ft_ipart(float n);
float	ft_fpart(float n);
float	ft_rfpart(float n);

#endif
