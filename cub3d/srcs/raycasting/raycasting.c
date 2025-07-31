/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:47:40 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/09 12:57:24 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
camera_x - ray position on player's plane(camera_x) and direction
map.x, map.y - coordinates of the map square the ray is in
delta_dist.x, delta_dist.y - ray lenght from one x-/y-side to next x-/y-side
side_dist.x, side_dist.y - ray lenght from curr position to next x-/y-side
*/

static void	raycasting_setup(t_ray *ray, t_cub3d *cub3d, int x)
{
	ray->camera_x = 2.0 * (double)x / (double)cub3d->win_width - 1.0;
	ray->dir.x = cub3d->player.dir.x + cub3d->player.plane.x * ray->camera_x;
	ray->dir.y = cub3d->player.dir.y + cub3d->player.plane.y * ray->camera_x;
	ray->map.x = (int)cub3d->player.pos.x;
	ray->map.y = (int)cub3d->player.pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
}

/*
wall_dist: distance to the wall hit by the ray
line_height: height of the vertical wall slice on screen
draw_start & draw_end: vertical coordinates where to draw 
the wall line (lowest and highest pixels)
*/

static void	calculate_wall_line(t_cub3d *cub3d, t_ray *ray)
{
	ray->line_height = (int)(cub3d->win_height / ray->wall_dist);
	ray->draw_start = - (ray->line_height) / 2 + cub3d->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + cub3d->win_height / 2;
	if (ray->draw_end >= cub3d->win_height)
		ray->draw_end = cub3d->win_height - 1;
}

void	raycasting(t_cub3d *cub3d)
{
	t_vec2i	pixel;

	pixel.x = 0;
	while (pixel.x < cub3d->win_width)
	{
		ft_bzero(&cub3d->ray, sizeof(t_ray));
		raycasting_setup(&cub3d->ray, cub3d, pixel.x);
		calculate_wall_dist(cub3d, &cub3d->ray);
		calculate_wall_line(cub3d, &cub3d->ray);
		draw_wall_line(cub3d, &cub3d->ray, pixel);
		draw_minimap_ray(cub3d, &cub3d->ray);
		pixel.x ++;
	}
}
