/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:57:50 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/22 13:13:08 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

static double	get_raw_wall_x(t_cub3d *cub3d, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = cub3d->player.pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = cub3d->player.pos.x + ray->wall_dist * ray->dir.x;
	return (wall_x - floor(wall_x));
}

static int	find_txtr_x_pos(t_cub3d *cub3d, t_ray *ray, t_txtr txtr)
{
	int		txtr_x_pos;
	double	raw_wall_x;

	if (ray->hit_type == HIT_ANIMATED_DOOR)
	{
		txtr_x_pos = (int)fmod(ray->door_texx, txtr.width);
		if (txtr_x_pos < 0)
			txtr_x_pos += txtr.width;
	}
	else if (ray->hit_type == HIT_WALL || ray->hit_type == HIT_CLOSED_DOOR)
	{
		raw_wall_x = get_raw_wall_x(cub3d, ray);
		if (ray->hit_type == HIT_CLOSED_DOOR)
		{
			if (ray->side == 0 && ray->dir.x < 0)
				raw_wall_x = 1.0 - raw_wall_x;
			else if (ray->side == 1 && ray->dir.y > 0)
				raw_wall_x = 1.0 - raw_wall_x;
		}
		txtr_x_pos = (int)(raw_wall_x * txtr.width);
	}
	return (txtr_x_pos);
}

static int	find_txtr_y_pos(t_cub3d *cub3d, t_ray *ray, t_txtr txtr, int y)
{
	int	txtr_y_pos;
	int	d;

	d = y * 256 - cub3d->win_height * 128 + ray->line_height * 128;
	txtr_y_pos = ((d * txtr.height) / ray->line_height) / 256;
	return (txtr_y_pos);
}

void	draw_wall_line_with_doors(t_cub3d *cub3d, t_ray *ray, t_vec2i pixel)
{
	int		colour;
	t_vec2i	txtr_pos;
	t_txtr	txtr;

	if (ray->hit_type == HIT_WALL || ray->hit_type == HIT_CLOSED_DOOR
		|| ray->hit_type == HIT_ANIMATED_DOOR)
	{
		txtr = choose_texture_for_line(cub3d, ray);
		txtr_pos.x = find_txtr_x_pos(cub3d, ray, txtr);
		pixel.y = ray->draw_start + 1;
		while (pixel.y < ray->draw_end)
		{
			txtr_pos.y = find_txtr_y_pos(cub3d, ray, txtr, pixel.y);
			colour = get_colour_from_texture(txtr, txtr_pos);
			colour = darken_colour(colour, ray->wall_dist);
			put_pixel_to_frame(cub3d, pixel.x, pixel.y, colour);
			pixel.y ++;
		}
	}
}
