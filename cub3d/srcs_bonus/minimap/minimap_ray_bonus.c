/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:28:33 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/18 15:06:09 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

static int	ft_abs(int n)
{
	if (n == -2147483648)
		return (2147483647);
	if (n < 0)
		return (-n);
	return (n);
}

static void	init_line_par(t_vec2i start, t_vec2i end, t_vec2i *d, t_vec2i *step)
{
	d->x = ft_abs(end.x - start.x);
	d->y = ft_abs(end.y - start.y);
	step->x = 1 - 2 * (start.x >= end.x);
	step->y = 1 - 2 * (start.y >= end.y);
}

/*Bresenham’s line algorithm*/
void	draw_line(t_cub3d *cub3d, t_vec2i start_p, t_vec2i end_p, int colour)
{
	t_vec2i	diff;
	t_vec2i	step_dir;
	int		err;
	int		e2;

	init_line_par(start_p, end_p, &diff, &step_dir);
	err = diff.x - diff.y;
	while (1)
	{
		put_pixel_to_frame(cub3d, start_p.x, start_p.y, colour);
		if (start_p.x == end_p.x && start_p.y == end_p.y)
			break ;
		e2 = 2 * err;
		if (e2 > -diff.y)
		{
			err -= diff.y;
			start_p.x += step_dir.x;
		}
		if (e2 < diff.x)
		{
			err += diff.x;
			start_p.y += step_dir.y;
		}
	}
}

void	draw_minimap_ray(t_cub3d *cub3d, t_ray *ray)
{
	t_vec2i	start_p;
	t_vec2i	end_p;

	start_p.x = (int)(cub3d->player.pos.x
			* MINIMAP_TILE_SIZE + MINIMAP_OFFSET_X);
	start_p.y = (int)(cub3d->player.pos.y
			* MINIMAP_TILE_SIZE + MINIMAP_OFFSET_Y);
	ray->map_hit.x = cub3d->player.pos.x + ray->dir.x * ray->wall_dist;
	ray->map_hit.y = cub3d->player.pos.y + ray->dir.y * ray->wall_dist;
	end_p.x = (int)(ray->map_hit.x * MINIMAP_TILE_SIZE + MINIMAP_OFFSET_X);
	end_p.y = (int)(ray->map_hit.y * MINIMAP_TILE_SIZE + MINIMAP_OFFSET_Y);
	draw_line(cub3d, start_p, end_p, MINIMAP_RAY_COLOUR);
}
