/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:28:06 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/24 13:40:09 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	handle_map_start(t_cub3d *cub3d, char *line)
{
	if (!cub3d->map_started)
		cub3d->map_started = true;
	parse_map(line, cub3d);
}

void	initialise_map_grid(t_cub3d *cub3d, int line_length)
{
	int		i;

	cub3d->map.grid = malloc(sizeof(char *) * MAX_MAP_HEIGHT);
	if (!cub3d->map.grid)
		print_and_exit("Memory allocation failed for map grid", cub3d);
	i = 0;
	while (i < MAX_MAP_HEIGHT)
	{
		cub3d->map.grid[i] = NULL;
		i++;
	}
	cub3d->map.height = 0;
	cub3d->map.width = line_length;
}

void	free_line_and_exit(char *cleaned_line, t_cub3d *cub3d)
{
	free(cleaned_line);
	print_and_exit("Memory allocation failed for map line", cub3d);
}

int	parse_map(const char *line, t_cub3d *cub3d)
{
	char	*cleaned_line;
	int		line_length;

	if (!cub3d || !line)
		print_and_exit("cub3D structure or line is NULL.", cub3d);
	if (cub3d->map.height + 1 == MAX_MAP_HEIGHT)
		return (print_and_return_error("Map height exceeds maximum limit set",
				0, cub3d), 0);
	cleaned_line = ft_strtrim(line, "\n\r");
	if (!cleaned_line)
		print_and_exit("Failed to trim line, line is NULL.", cub3d);
	line_length = ft_strlen(cleaned_line);
	if (!cub3d->map.grid)
		initialise_map_grid(cub3d, line_length);
	find_and_store_player_position(cub3d, cleaned_line);
	cub3d->map.grid[cub3d->map.height] = ft_strdup(cleaned_line);
	if (!cub3d->map.grid[cub3d->map.height])
		free_line_and_exit(cleaned_line, cub3d);
	if (line_length > cub3d->map.width)
		cub3d->map.width = line_length;
	cub3d->map.height++;
	free(cleaned_line);
	return (1);
}

int	player_direction_to_vector(t_cub3d *cub3d)
{
	if (!cub3d)
		print_and_return("Cub3D structure is NULL.", 0);
	if (cub3d->map.player_orientation == 'N'
		|| cub3d->map.player_orientation == 'S')
		north_south(cub3d);
	else if (cub3d->map.player_orientation == 'E'
		|| cub3d->map.player_orientation == 'W')
		east_west(cub3d);
	return (1);
}
