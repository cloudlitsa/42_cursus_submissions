/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:08:32 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/23 21:52:49 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

char	player_within_bounds(t_cub3d *cub3d, int x, int y)
{
	if (y < 0 || y >= cub3d->map.height)
		return ('\0');
	if (!cub3d->map.grid[y])
		return ('\0');
	if (x < 0 || x >= (int)ft_strlen(cub3d->map.grid[y]))
		return ('\0');
	return (cub3d->map.grid[y][x]);
}

int	is_walkable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D')
		return (1);
	return (0);
}

int	floodfill(t_cub3d *cub3d, int x, int y)
{
	char	current_pos;

	current_pos = player_within_bounds(cub3d, x, y);
	if (current_pos == '\0' || current_pos == ' ')
		return (0);
	if (current_pos == '1' || current_pos == '2')
		return (1);
	if (is_walkable(current_pos))
	{
		cub3d->map.grid[y][x] = '2';
		if (!floodfill(cub3d, x + 1, y)
			|| !floodfill(cub3d, x - 1, y)
			|| !floodfill(cub3d, x, y + 1)
			|| !floodfill(cub3d, x, y - 1))
			print_and_exit("Map is not surrounded by walls \
or player outside walls", cub3d);
	}
	return (1);
}

void	restore_map(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub3d->map.height)
	{
		if (cub3d->map.grid[y])
		{
			x = 0;
			while (x < (int)ft_strlen(cub3d->map.grid[y]))
			{
				if (cub3d->map.grid[y][x] == '2')
				{
					if (y == (int)cub3d->player.pos.y
						&& x == (int)cub3d->player.pos.x)
						cub3d->map.grid[y][x] = cub3d->map.player_orientation;
					else
						cub3d->map.grid[y][x] = '0';
				}
				x++;
			}
		}
		y++;
	}
}

int	validate_map(t_cub3d *cub3d)
{
	int	player_x;
	int	player_y;
	int	result;

	if (!cub3d || !cub3d->map.grid || cub3d->map.player_orientation == '\0')
		print_and_return("map or player not initialised.", 0);
	player_x = (int)cub3d->player.pos.x;
	player_y = (int)cub3d->player.pos.y;
	result = floodfill(cub3d, player_x, player_y);
	restore_map(cub3d);
	restore_doors_to_map(cub3d);
	if (result == 1)
	{
		cub3d->is_map_valid = true;
		return (1);
	}
	else
		return (print_and_return("Map not surrounded by walls.\n", 0));
}
