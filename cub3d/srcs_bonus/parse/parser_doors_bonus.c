/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_doors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:08:29 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/23 19:25:02 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

int	find_and_store_doors(t_cub3d *cub3d, const char *line)
{
	int	i;
	int	door_idx;

	if (!cub3d || !line)
		game_error("Cub3D structure or line is NULL.", 0);
	i = 0;
	while (line[i])
	{
		if (line[i] == 'D')
		{
			door_idx = cub3d->door_count;
			if (door_idx >= DOORS_MAX)
				return (print_and_return_error
					("Door limit exceeded for this map", 0, cub3d), 0);
			cub3d->doors[door_idx].is_locked = false;
			cub3d->doors[door_idx].map_pos.x = i;
			cub3d->doors[door_idx].map_pos.y = cub3d->map.height;
			cub3d->doors[door_idx].state = CLOSED;
			cub3d->doors[door_idx].timer = 0.0f;
			cub3d->door_count += 1;
		}
		i ++;
	}
	return (0);
}

void	restore_doors_to_map(t_cub3d *cub3d)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	while (i < cub3d->door_count)
	{
		x = cub3d->doors[i].map_pos.x;
		y = cub3d->doors[i].map_pos.y;
		if (y >= 0 && y < cub3d->map.height
			&& x >= 0 && x < (int)ft_strlen(cub3d->map.grid[y])
			&& cub3d->map.grid[y])
			cub3d->map.grid[y][x] = 'D';
		i++;
	}
}
