/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:04:03 by mosokina          #+#    #+#             */
/*   Updated: 2025/06/25 16:08:08 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//both camera direction and camera plane must be rotate
static void	rotate(t_player *pl, double rot_speed)
{
	t_vec2d	old_dir;
	t_vec2d	old_plane;

	old_dir.x = pl->dir.x;
	old_plane.x = pl->plane.x;
	pl->dir.x = pl->dir.x * cos(rot_speed) - pl->dir.y * sin(rot_speed);
	pl->dir.y = old_dir.x * sin(rot_speed) + pl->dir.y * cos(rot_speed);
	pl->plane.x = pl->plane.x * cos(rot_speed) - pl->plane.y * sin(rot_speed);
	pl->plane.y = old_plane.x * sin(rot_speed) + pl->plane.y * cos(rot_speed);
}

void	rotate_to_left(t_player *pl)
{
	double	rot_speed;

	rot_speed = -ROTATE_SPEED;
	rotate(pl, rot_speed);
}

void	rotate_to_right(t_player *pl)
{
	double	rot_speed;

	rot_speed = ROTATE_SPEED;
	rotate(pl, rot_speed);
}
