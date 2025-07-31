/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_doors_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:54:41 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/22 20:01:42 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

static void	process_y_side(t_ray *ray, t_vec2d *player_pos, double open_amount)
{
	ray->wall_dist = (ray->map.y - player_pos->y
			+ (1 - ray->step.y) / 2.0) / ray->dir.y;
	ray->door_hit_x = player_pos->x + ray->wall_dist * ray->dir.x;
	ray->door_hit_x -= floor(ray->door_hit_x);
	if (ray->step.y == 1)
		ray->door_hit_x = 1.0 - ray->door_hit_x;
	if (ray->door_hit_x < open_amount)
		ray->hit_type = PASS_THR_ANIMATED_DOOR;
	else
		ray->hit_type = HIT_ANIMATED_DOOR;
}

static void	process_x_side(t_ray *ray, t_vec2d *player_pos, double open_amount)
{
	ray->wall_dist = (ray->map.x - player_pos->x
			+ (1 - ray->step.x) / 2.0) / ray->dir.x;
	ray->door_hit_x = player_pos->y + ray->wall_dist * ray->dir.y;
	ray->door_hit_x -= floor(ray->door_hit_x);
	if (ray->step.x == -1)
		ray->door_hit_x = 1.0 - ray->door_hit_x;
	if (ray->door_hit_x < open_amount)
		ray->hit_type = PASS_THR_ANIMATED_DOOR;
	else
		ray->hit_type = HIT_ANIMATED_DOOR;
}

static void	calc_offset(t_ray *ray, t_vec2d *player_pos, t_door *door)
{
	double	open_amount;
	double	timer_clamped;

	timer_clamped = door->timer;
	if (timer_clamped < 0)
		timer_clamped = 0;
	if (timer_clamped > DOOR_DURATION)
		timer_clamped = DOOR_DURATION;
	open_amount = timer_clamped / DOOR_DURATION;
	if (ray->side == 1)
		process_y_side(ray, player_pos, open_amount);
	else
		process_x_side(ray, player_pos, open_amount);
}

void	door_tex_correction(t_ray *ray, double open_amount, int tex_width)
{
	double	hit_pos_on_door;
	double	visible_range;

	hit_pos_on_door = ray->door_hit_x;
	visible_range = 1.0 - open_amount;
	if (visible_range < 0.001)
		visible_range = 0.001;
	ray->door_texx = (int)(((hit_pos_on_door - open_amount)
				/ visible_range) * tex_width);
	if (ray->door_texx < 0)
		ray->door_texx = 0;
	if (ray->door_texx >= tex_width)
		ray->door_texx = tex_width - 1;
}

void	process_animated_door_hit(t_ray *ray, t_cub3d *cub3d, t_door *door)
{
	double	timer_clamped;
	double	open_amount;

	calc_offset(ray, &cub3d->player.pos, door);
	if (ray->hit_type == HIT_ANIMATED_DOOR)
	{
		timer_clamped = door->timer;
		if (timer_clamped < 0)
			timer_clamped = 0;
		if (timer_clamped > DOOR_DURATION)
			timer_clamped = DOOR_DURATION;
		open_amount = timer_clamped / DOOR_DURATION;
		door_tex_correction(ray, open_amount, cub3d->txtrs[TX_DOOR].width);
	}
}
