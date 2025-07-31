/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:50:10 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/18 15:06:13 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

int	can_walk(t_cub3d *cub3d, double x, double y)
{
	t_door	*door;

	if (x < 0 || y < 0 || y >= cub3d->map.height || x >= cub3d->map.width)
		return (false);
	if (cub3d->map.grid[(int)y][(int)x] == '1')
		return (false);
	if (cub3d->map.grid[(int)y][(int)x] == 'D')
	{
		door = get_door_at_pos(cub3d, (int)x, (int)y);
		if (door->state != OPEN)
			return (false);
	}
	return (true);
}

void	handle_input(t_cub3d *cub3d, t_player *pl)
{
	if (pl->move_forward)
		move_forward(cub3d, pl);
	if (pl->move_backward)
		move_backward(cub3d, pl);
	if (pl->strafe_left)
		strafe_left(cub3d, pl);
	if (pl->strafe_right)
		strafe_right(cub3d, pl);
	if (pl->rotate_left)
		rotate_to_left(pl);
	if (pl->rotate_right)
		rotate_to_right(pl);
}
