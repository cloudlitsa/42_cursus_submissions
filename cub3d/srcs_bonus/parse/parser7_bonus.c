/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser7_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:21:46 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/24 13:55:19 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

void	north_south(t_cub3d *cub3d)
{
	if (cub3d->map.player_orientation == 'N')
	{
		cub3d->player.dir.x = 0.0;
		cub3d->player.dir.y = -1.0;
		cub3d->player.plane.x = PLANE;
		cub3d->player.plane.y = 0.0;
	}
	else if (cub3d->map.player_orientation == 'S')
	{
		cub3d->player.dir.x = 0.0;
		cub3d->player.dir.y = 1.0;
		cub3d->player.plane.x = -PLANE;
		cub3d->player.plane.y = 0.0;
	}
}

void	east_west(t_cub3d *cub3d)
{
	if (cub3d->map.player_orientation == 'E')
	{
		cub3d->player.dir.x = 1.0;
		cub3d->player.dir.y = 0.0;
		cub3d->player.plane.x = 0.0;
		cub3d->player.plane.y = PLANE;
	}
	else if (cub3d->map.player_orientation == 'W')
	{
		cub3d->player.dir.x = -1.0;
		cub3d->player.dir.y = 0.0;
		cub3d->player.plane.x = 0.0;
		cub3d->player.plane.y = -PLANE;
	}
}

int	find_and_store_player_position(t_cub3d *cub3d, const char *line)
{
	int	i;

	if (!line)
		print_and_exit("Failed to trim line, line is NULL.", cub3d);
	if (!cub3d || !line)
		print_and_exit("Cub3D structure or line is NULL.", cub3d);
	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (cub3d->map.player_orientation != '\0')
				return (print_and_return_error
					("Multiple player positions found", 0, cub3d), 0);
			cub3d->map.player_orientation = line[i];
			cub3d->player.pos.x = i;
			cub3d->player.pos.y = cub3d->map.height;
		}
		i++;
	}
	return (0);
}

static void	zero_outside_map(t_cub3d *cub3d, t_map *map)
{
	int	i;
	int	len;

	i = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->grid[i]);
		if (map->grid[i][len - 1] == '0')
			print_and_exit("Zero ourside line.", cub3d);
		i ++;
	}
}

int	finalise_parsing(t_cub3d *cub3d)
{
	if (!cub3d)
		print_and_exit("cub3D structure is NULL.", NULL);
	if (cub3d->error)
		return (0);
	check_all_textures_loaded(cub3d);
	if (!cub3d->is_textures_loaded)
		return (print_and_return_error("Textures not loaded.", 0, cub3d), 0);
	if (!cub3d->is_colours_set)
		return (print_and_return_error("Colours are not set.", 0, cub3d), 0);
	if (!validate_map(cub3d))
		print_and_exit("Map validation failed.", cub3d);
	zero_outside_map(cub3d, &cub3d->map);
	if (cub3d->map.player_orientation == '\0')
		return (print_and_return_error("Player missing.", 0, cub3d));
	if (cub3d->map.grid == NULL || cub3d->map.height == 0
		|| cub3d->map.width == 0)
		print_and_exit("Map grid is not properly initialized.", cub3d);
	player_direction_to_vector(cub3d);
	printf(G"√"RESET" Parsing and validation completed successfully.\n");
	return (1);
}
