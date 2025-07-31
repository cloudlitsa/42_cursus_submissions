/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:13:39 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/23 12:43:20 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*drawing each minimap tile as a 5×5 pixel square*/
static int	draw_minimap_tile(t_cub3d *cub3d, int x, int y, int colour)
{
	int	j;
	int	i;
	int	size;

	j = 0;
	i = 0;
	size = MINIMAP_TILE_SIZE;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_to_frame(cub3d, x + i + MINIMAP_OFFSET_X,
				y + j + MINIMAP_OFFSET_Y, colour);
			j ++;
		}
		i ++;
	}
	return (0);
}

static int	draw_minimap_player(t_cub3d *cub3d, double map_x, double map_y)
{
	int	px;
	int	py;

	px = (int)(map_x * MINIMAP_TILE_SIZE - MINIMAP_PLAYER_SIZE / 2);
	py = (int)(map_y * MINIMAP_TILE_SIZE - MINIMAP_PLAYER_SIZE / 2);
	draw_minimap_tile(cub3d, px, py, MINIMAP_PLAYER_COLOUR);
	return (0);
}

/*	draw walls and player on 2d minimap */
void	draw_minimap(t_cub3d *cub3d)
{
	int		map_x;
	int		map_y;

	map_y = 0;
	while (map_y < cub3d->map.height)
	{
		map_x = 0;
		while (cub3d->map.grid[map_y][map_x])
		{
			if (cub3d->map.grid[map_y][map_x] == '1')
				draw_minimap_tile(cub3d, map_x * MINIMAP_TILE_SIZE,
					map_y * MINIMAP_TILE_SIZE, MINIMAP_WALLS_COLOUR);
			map_x ++;
		}
		map_y ++;
	}
	if (can_walk(&cub3d->map, cub3d->player.pos.x, cub3d->player.pos.y))
		draw_minimap_player(cub3d, cub3d->player.pos.x, cub3d->player.pos.y);
}
