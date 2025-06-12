/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakslee <hakslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:49:32 by dong-hki          #+#    #+#             */
/*   Updated: 2025/06/09 10:55:12 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "mlx.h"
#include "libft.h"
#include "ft_printf.h"
#include "game.h"

static void	free_map_copy(char **map_copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static char	**create_map_with_player(t_game *game)
{
	char	**map_copy;
	int		i;
	int		player_map_x;
	int		player_map_y;

	map_copy = ft_calloc(game->map_rows + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map_rows)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			free_map_copy(map_copy, i);
			return (NULL);
		}
		i++;
	}
	player_map_x = (int)game->player_x;
	player_map_y = (int)game->player_y;
	if (player_map_y < game->map_rows && player_map_x < game->map_cols)
		map_copy[player_map_y][player_map_x] = 'P';
	return (map_copy);
}

void	print_map_for_debug(t_game *game)
{
	char	**map_with_player;
	int		i;

	map_with_player = create_map_with_player(game);
	if (!map_with_player)
		return ;
	write(1, "\033[H\033[J", 7);
	i = 0;
	while (i < game->map_rows)
	{
		ft_putendl_fd(map_with_player[i], 1);
		i++;
	}
	free_map_copy(map_with_player, game->map_rows);
	ft_printf("----------------------------------------\n");
	ft_printf("Player Position: (X=%.2f, Y=%.2f)\n",
		game->player_x, game->player_y);
	ft_printf("Direction Vector: (X=%.2f, Y=%.2f)\n", game->dir_x, game->dir_y);
	ft_printf("Camera Plane:   (X=%.2f, Y=%.2f)\n",
		game->plane_x, game->plane_y);
	ft_printf("----------------------------------------\n");
}
