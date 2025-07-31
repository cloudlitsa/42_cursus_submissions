/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:41:46 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/22 11:27:42 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

t_txtr	choose_texture_for_line(t_cub3d *cub3d, t_ray *ray)
{
	t_txtr	txtr;

	if (ray->hit_type == HIT_ANIMATED_DOOR
		|| ray->hit_type == HIT_CLOSED_DOOR)
		txtr = cub3d->txtrs[TX_DOOR];
	else if (ray->hit_type == HIT_WALL)
	{
		if (ray->side == 0)
		{
			if (ray->dir.x > 0)
				txtr = cub3d->txtrs[TX_EAST];
			else
				txtr = cub3d->txtrs[TX_WEST];
		}
		else
		{
			if (ray->dir.y > 0)
				txtr = cub3d->txtrs[TX_SOUTH];
			else
				txtr = cub3d->txtrs[TX_NORTH];
		}
	}
	return (txtr);
}
