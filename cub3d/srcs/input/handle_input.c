/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:50:10 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/14 11:26:36 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	can_walk(t_map *map, double x, double y)
{
	if (x < 0 || y < 0 || y >= map->height || x >= map->width)
		return (0);
	return (map->grid[(int)y][(int)x] != '1');
}

void	handle_input(t_cub3d *cub3d, t_player *pl)
{
	if (pl->move_forward)
		move_forward(&cub3d->map, pl);
	if (pl->move_backward)
		move_backward(&cub3d->map, pl);
	if (pl->strafe_left)
		strafe_left(&cub3d->map, pl);
	if (pl->strafe_right)
		strafe_right(&cub3d->map, pl);
	if (pl->rotate_left)
		rotate_to_left(pl);
	if (pl->rotate_right)
		rotate_to_right(pl);
}
