/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:57:50 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/23 13:00:38 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	find_txtr_x_pos(t_cub3d *cub3d, t_ray *ray, t_txtr wall_txtr)
{
	double	wall_x;
	int		txtr_x_pos;

	if (ray->side == 0)
		wall_x = cub3d->player.pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = cub3d->player.pos.x + ray->wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	txtr_x_pos = (int)(wall_x * wall_txtr.width);
	if (ray->side == 0 && ray->dir.x > 0)
		txtr_x_pos = wall_txtr.width - txtr_x_pos - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		txtr_x_pos = wall_txtr.width - txtr_x_pos - 1;
	return (txtr_x_pos);
}

static int	find_txtr_y_pos(t_cub3d *cub3d, t_ray *ray, t_txtr wall_txtr, int y)
{
	int	txtr_y_pos;
	int	d;

	d = y * 256 - cub3d->win_height * 128 + ray->line_height * 128;
	txtr_y_pos = ((d * wall_txtr.height) / ray->line_height) / 256;
	return (txtr_y_pos);
}

static t_txtr	choose_wall_texture(t_cub3d *cub3d, t_ray *ray)
{
	t_txtr	wall_txtr;

	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			wall_txtr = cub3d->txtrs[TX_EAST];
		else
			wall_txtr = cub3d->txtrs[TX_WEST];
	}
	else
	{
		if (ray->dir.y > 0)
			wall_txtr = cub3d->txtrs[TX_SOUTH];
		else
			wall_txtr = cub3d->txtrs[TX_NORTH];
	}
	return (wall_txtr);
}

void	draw_wall_line(t_cub3d *cub3d, t_ray *ray, t_vec2i pixel)
{
	int		colour;
	t_vec2i	txtr_pos;
	t_txtr	wall_txtr;

	wall_txtr = choose_wall_texture(cub3d, ray);
	txtr_pos.x = find_txtr_x_pos(cub3d, ray, wall_txtr);
	pixel.y = ray->draw_start + 1;
	while (pixel.y < ray->draw_end)
	{
		txtr_pos.y = find_txtr_y_pos(cub3d, ray, wall_txtr, pixel.y);
		colour = get_colour_from_texture(wall_txtr, txtr_pos);
		colour = darken_colour(colour, ray->wall_dist);
		put_pixel_to_frame(cub3d, pixel.x, pixel.y, colour);
		pixel.y ++;
	}
}
