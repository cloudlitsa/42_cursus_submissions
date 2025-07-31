/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:01:42 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/18 15:06:10 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

void	moving(t_cub3d *cub3d, t_player *pl, t_vec2d dir)
{
	double	offset;
	double	new_x;
	double	new_y;

	offset = MOVE_SPEED + COLLISION_BUFFER;
	new_x = pl->pos.x + dir.x * MOVE_SPEED;
	new_y = pl->pos.y + dir.y * MOVE_SPEED;
	if (can_walk(cub3d, pl->pos.x + dir.x * offset, pl->pos.y))
		pl->pos.x = new_x;
	if (can_walk(cub3d, pl->pos.x, pl->pos.y + dir.y * offset))
		pl->pos.y = new_y;
}

void	move_forward(t_cub3d *cub3d, t_player *pl)
{
	moving(cub3d, pl, pl->dir);
}

void	move_backward(t_cub3d *cub3d, t_player *pl)
{
	t_vec2d	back;

	back.x = -pl->dir.x;
	back.y = -pl->dir.y;
	moving(cub3d, pl, back);
}

void	strafe_left(t_cub3d *cub3d, t_player *pl)
{
	t_vec2d	left;

	left.x = -pl->plane.x;
	left.y = -pl->plane.y;
	moving(cub3d, pl, left);
}

void	strafe_right(t_cub3d *cub3d, t_player *pl)
{
	moving(cub3d, pl, pl->plane);
}
