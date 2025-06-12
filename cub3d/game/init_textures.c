/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:14:42 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/08 16:38:53 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "mlx.h"
#include "game.h"

static int	load_one_texture(void *mlx_ptr, const char *path, t_tex *dest)
{
	int	w;
	int	h;

	dest->img = mlx_xpm_file_to_image(mlx_ptr, (char *)path, &w, &h);
	if (!dest->img)
	{
		ft_putstr_fd("Error: Failed to load texture ", STDERR_FILENO);
		ft_putendl_fd((char *)path, STDERR_FILENO);
		return (-1);
	}
	dest->width = w;
	dest->height = h;
	dest->data_addr = mlx_get_data_addr(dest->img,
			&dest->bpp, &dest->line_len, &dest->endian);
	return (0);
}

int	load_wall_textures(t_game *game)
{
	void	*mlx_ptr;
	t_tex	*tex;

	mlx_ptr = game->mlx_wrap->mlx_ptr;
	tex = game->tex;
	if (load_one_texture(mlx_ptr, game->cfg->tex_no, &tex[TEX_NORTH]) < 0)
		return (-1);
	if (load_one_texture(mlx_ptr, game->cfg->tex_so, &tex[TEX_SOUTH]) < 0)
		return (-1);
	if (load_one_texture(mlx_ptr, game->cfg->tex_we, &tex[TEX_WEST]) < 0)
		return (-1);
	if (load_one_texture(mlx_ptr, game->cfg->tex_ea, &tex[TEX_EAST]) < 0)
		return (-1);
	return (0);
}

int	load_sprite_texture(t_game *game)
{
	void	*mlx_ptr;
	t_tex	*tex;

	if (!game->cfg->tex_sprite)
	{
		game->tex[TEX_SPRITE].img = NULL;
		return (0);
	}
	mlx_ptr = game->mlx_wrap->mlx_ptr;
	tex = game->tex;
	if (load_one_texture(mlx_ptr, game->cfg->tex_sprite, &tex[TEX_SPRITE]) < 0)
		return (-1);
	return (0);
}

int	load_all_textures(t_game *game)
{
	game->tex = (t_tex *)malloc(sizeof(t_tex) * TEX_COUNT);
	if (!game->tex)
	{
		ft_putendl_fd("Error: malloc tex array failed", STDERR_FILENO);
		return (-1);
	}
	ft_memset(game->tex, 0, sizeof(t_tex) * TEX_COUNT);
	if (load_wall_textures(game) < 0)
		return (-1);
	if (load_sprite_texture(game) < 0)
		return (-1);
	return (0);
}

void	unload_all_textures(t_game *game)
{
	void	*mlx_ptr;
	int		i;

	if (!game->tex)
		return ;
	mlx_ptr = game->mlx_wrap->mlx_ptr;
	i = 0;
	while (i < TEX_COUNT)
		if (game->tex[i++].img)
			mlx_destroy_image(mlx_ptr, game->tex[i].img);
	free(game->tex);
}
