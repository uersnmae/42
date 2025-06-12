/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:13:04 by dong-hki          #+#    #+#             */
/*   Updated: 2025/03/03 19:35:08 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "mlx.h"
#include "fdf.h"

static t_fdf	*init(char *path)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		error_return(NULL, "Mallocating fdf failed", NON_SYS);
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->img_ptr = NULL;
	fdf->data_addr = NULL;
	fdf->depth = NULL;
	fdf->object = NULL;
	fdf->cam = NULL;
	fdf->map = NULL;
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		error_return(fdf, "Initializing mlx_ptr failed", NON_SYS);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, path);
	if (!fdf->win_ptr)
		error_return(fdf, "Creating new window failed", NON_SYS);
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	if (!fdf->img_ptr)
		error_return(fdf, "Creating new image failed", NON_SYS);
	fdf->data_addr = mlx_get_data_addr(fdf->img_ptr, &fdf->bpp,
			&fdf->size_line, &fdf->endian);
	return (fdf);
}

static t_map	*init_map(t_fdf *fdf)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		error_return(fdf, "Mallocating map failed", NON_SYS);
	map->width = 0;
	map->height = 0;
	map->z_min = 0;
	map->z_max = 0;
	map->grid = NULL;
	return (map);
}

static t_object	*init_object(t_fdf *fdf)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		error_return(fdf, "Mallocating object failed", NON_SYS);
	object->angle_x = get_radian(0);
	object->angle_y = get_radian(0);
	object->angle_z = get_radian(0);
	object->scale = get_min(WIDTH / fdf->map->width / 2,
			HEIGHT / fdf->map->height / 2);
	object->offset_x = 0;
	object->offset_y = 0;
	object->height_z = 1;
	return (object);
}

static t_camera	*init_camera(t_fdf *fdf)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		error_return(fdf, "Mallocating camera failed", NON_SYS);
	cam->pos_x = 0.0;
	cam->pos_y = 0.0;
	cam->pos_z = 0.0;
	cam->rot_x = get_radian(120);
	cam->rot_y = get_radian(30);
	cam->rot_z = 0.0;
	cam->toggle = 0;
	return (cam);
}

int	main(int argc, char *argv[])
{
	t_fdf	*fdf;

	fdf = NULL;
	if (argc == 2)
	{
		fdf = init(argv[1]);
		fdf->map = init_map(fdf);
		check_map(fdf, argv[1], fdf->map);
		fdf->object = init_object(fdf);
		fdf->cam = init_camera(fdf);
		fdf->depth = init_depth(fdf);
		init_hook(fdf);
		wireframe(fdf->map, fdf);
		mlx_loop(fdf->mlx_ptr);
	}
	else
		error_return(fdf, "Usage: ./fdf <mapfile>.fdf", NON_SYS);
	return (EXIT_SUCCESS);
}
