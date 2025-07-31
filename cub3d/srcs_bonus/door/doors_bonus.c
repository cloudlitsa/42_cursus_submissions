/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:06:42 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/18 20:08:39 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

static int	is_door_within_reach(t_cub3d *cub3d, t_door *door)
{
	float	dx;
	float	dy;
	float	distance_squared;
	float	interact_radius;

	interact_radius = 3.5f * 3.5f;
	dx = cub3d->player.pos.x - (door->map_pos.x + 0.5f);
	dy = cub3d->player.pos.y - (door->map_pos.y + 0.5f);
	distance_squared = dx * dx + dy * dy;
	return (distance_squared < interact_radius);
}

static int	is_door_in_front(t_cub3d *cub3d, t_door *door)
{
	t_vec2d	to_door;
	float	length;
	float	dot;

	to_door.x = (door->map_pos.x + 0.5f) - cub3d->player.pos.x;
	to_door.y = (door->map_pos.y + 0.5f) - cub3d->player.pos.y;
	length = sqrtf(to_door.x * to_door.x + to_door.y * to_door.y);
	if (length == 0.0f)
		return (0);
	to_door.x /= length;
	to_door.y /= length;
	dot = to_door.x * cub3d->player.dir.x + to_door.y * cub3d->player.dir.y;
	return (dot > 0.75f);
}

void	trigger_door_action(t_cub3d *cub3d)
{
	t_door	*door;
	int		i;

	i = 0;
	while (i < cub3d->door_count)
	{
		door = &cub3d->doors[i];
		if (is_door_within_reach(cub3d, door) && is_door_in_front(cub3d, door))
		{
			if (door->is_locked)
				printf("THE DOOR IS LOCKED\n");
			else if (door->state == CLOSED)
			{
				door->state = OPENING;
				cub3d->animated_door = door;
			}
			else if (door->state == OPEN)
			{
				door->state = CLOSING;
				cub3d->animated_door = door;
			}
			break ;
		}
		i ++;
	}
}

void	animate_door(t_cub3d *cub3d, double delta_time)
{
	t_door	*door;

	door = cub3d->animated_door;
	if (door == NULL)
		return ;
	if (door->state == OPENING)
	{
		door->timer += delta_time;
		if (door->timer >= DOOR_DURATION)
		{
			door->timer = DOOR_DURATION;
			door->state = OPEN;
			cub3d->animated_door = NULL;
		}
	}
	else if (door->state == CLOSING)
	{
		door->timer -= delta_time;
		if (door->timer <= 0.0f)
		{
			door->timer = 0.0f;
			door->state = CLOSED;
			cub3d->animated_door = NULL;
		}
	}
}

t_door	*get_door_at_pos(t_cub3d *cub3d, int x, int y)
{
	int	i;

	i = 0;
	while (i < cub3d->door_count)
	{
		if (cub3d->doors[i].map_pos.x == x && cub3d->doors[i].map_pos.y == y)
			return (&cub3d->doors[i]);
		i ++;
	}
	return (NULL);
}
