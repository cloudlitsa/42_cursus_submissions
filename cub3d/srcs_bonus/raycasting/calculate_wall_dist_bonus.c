/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_wall_dist_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:56:58 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/18 15:06:06 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

/*
step.x, step.y - what direction to step in x or y-direction (eighter +1 or -1);
side_dist.x or side_dist.y - distance from the ray start position to the
next x-/y- position
*/

static void	dda_setup(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y)
			* ray->delta_dist.y;
	}
}

void	handle_hit(t_cub3d *cub3d, t_ray *ray)
{
	char	map_char;
	t_door	*checking_door;

	map_char = cub3d->map.grid[ray->map.y][ray->map.x];
	if (map_char == '1')
		ray->hit_type = HIT_WALL;
	else if (map_char == 'D')
	{
		checking_door = get_door_at_pos(cub3d, ray->map.x, ray->map.y);
		if (checking_door == NULL)
			ray->hit_type = NO_HIT;
		else if (checking_door->state == OPEN)
			ray->hit_type = NO_HIT;
		else if (checking_door->state == CLOSED)
			ray->hit_type = HIT_CLOSED_DOOR;
		else if (checking_door->state == OPENING
			|| checking_door->state == CLOSING)
			process_animated_door_hit(ray, cub3d, checking_door);
	}
}

static void	dda_perform(t_cub3d *cub3d, t_ray *ray)
{
	ray->hit_type = NO_HIT;
	while (ray->hit_type == NO_HIT || ray->hit_type == PASS_THR_ANIMATED_DOOR)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (ray->map.y < 0 || ray->map.y >= cub3d->map.height
			|| ray->map.x < 0 || ray->map.x >= cub3d->map.width
			|| cub3d->map.grid[ray->map.y] == NULL)
		{
			ray->hit_type = HIT_WALL;
			break ;
		}
		handle_hit(cub3d, ray);
	}
}

void	calculate_wall_dist_with_doors(t_cub3d *cub3d, t_ray *ray)
{
	dda_setup(ray, &cub3d->player);
	dda_perform(cub3d, ray);
	if (ray->hit_type == HIT_WALL || ray->hit_type == HIT_CLOSED_DOOR
		|| ray->hit_type == HIT_ANIMATED_DOOR)
	{
		if (ray->side == 0)
			ray->wall_dist = (ray->map.x - cub3d->player.pos.x
					+ (1 - ray->step.x) / 2.0) / ray->dir.x;
		else
			ray->wall_dist = (ray->map.y - cub3d->player.pos.y
					+ (1 - ray->step.y) / 2.0) / ray->dir.y;
		if (ray->wall_dist < 0.0001)
			ray->wall_dist = 0.0001;
	}
}
