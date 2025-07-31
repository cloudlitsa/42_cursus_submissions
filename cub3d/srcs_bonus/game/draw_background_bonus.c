/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:48:05 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/23 19:37:22 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

/*Calculates the direction and world position of a floor (or ceiling) pixel 
at a given screen coordinate, and maps 
it to corresponding texture coordinates for sampling.
*/

void	set_txtr_pos(t_cub3d *cub3d, t_floor *fl, t_vec2i *tx_pos, int tx_indx)
{
	fl->dir.x = cub3d->player.dir.x + cub3d->player.plane.x * fl->camera_x;
	fl->dir.y = cub3d->player.dir.y + cub3d->player.plane.y * fl->camera_x;
	fl->floor_pos.x = cub3d->player.pos.x + fl->floor_dist * fl->dir.x;
	fl->floor_pos.y = cub3d->player.pos.y + fl->floor_dist * fl->dir.y;
	tx_pos->x = ((int)(fl->floor_pos.x * cub3d->txtrs[tx_indx].width))
		% cub3d->txtrs[tx_indx].width;
	tx_pos->y = ((int)(fl->floor_pos.y * cub3d->txtrs[tx_indx].height))
		% cub3d->txtrs[tx_indx].height;
	if (tx_pos->x < 0)
		tx_pos->x += cub3d->txtrs[tx_indx].width;
	if (tx_pos->y < 0)
		tx_pos->y += cub3d->txtrs[tx_indx].height;
}

static void	draw_floor_row(t_cub3d *cub3d, int y_coord, double floor_dist)
{
	t_vec2i	pixel_pos;
	t_vec2i	tx_pos_floor;
	int		colour;
	t_floor	floor_ray;

	pixel_pos.y = y_coord;
	floor_ray.floor_dist = floor_dist;
	pixel_pos.x = 0;
	while (pixel_pos.x < cub3d->win_width)
	{
		floor_ray.camera_x = 2.0 * pixel_pos.x / cub3d->win_width - 1.0;
		set_txtr_pos(cub3d, &floor_ray, &tx_pos_floor, TX_FLOOR);
		colour = get_colour_from_texture(cub3d->txtrs[TX_FLOOR], tx_pos_floor);
		colour = darken_colour(colour, floor_ray.floor_dist);
		put_pixel_to_frame(cub3d, pixel_pos.x, pixel_pos.y, colour);
		pixel_pos.x++;
	}
}

static void	draw_ceiling_row(t_cub3d *cub3d, int y_coord, double floor_dist)
{
	t_vec2i	pixel_pos;
	t_vec2i	tx_pos_ceil;
	int		colour;
	t_floor	ceil_ray;

	ceil_ray.floor_dist = floor_dist;
	pixel_pos.y = y_coord;
	pixel_pos.x = 0;
	while (pixel_pos.x < cub3d->win_width)
	{
		ceil_ray.camera_x = 2.0 * pixel_pos.x / cub3d->win_width - 1.0;
		set_txtr_pos(cub3d, &ceil_ray, &tx_pos_ceil, TX_CEILING);
		colour = get_colour_from_texture(cub3d->txtrs[TX_CEILING], tx_pos_ceil);
		colour = darken_colour(colour, ceil_ray.floor_dist);
		put_pixel_to_frame(cub3d, pixel_pos.x, cub3d->win_height
			- pixel_pos.y, colour);
		pixel_pos.x++;
	}
}

void	draw_background_with_txtr(t_cub3d *cub3d)
{
	int		y_coord;
	double	floor_dist;

	y_coord = cub3d->win_height / 2 + 1;
	while (y_coord < cub3d->win_height)
	{
		floor_dist = (double)cub3d->win_height
			/ (2.0 * y_coord - cub3d->win_height);
		draw_floor_row(cub3d, y_coord, floor_dist);
		draw_ceiling_row(cub3d, y_coord, floor_dist);
		y_coord ++;
	}
}

void	draw_background_with_colour(t_cub3d	*cub3d)
{
	int	x;
	int	y;

	x = 0;
	while (x < cub3d->win_width)
	{
		y = 0;
		while (y < cub3d->win_height)
		{
			if (y < cub3d->win_height / 2)
				put_pixel_to_frame(cub3d, x, y, cub3d->colours.ceiling_colour);
			else
				put_pixel_to_frame(cub3d, x, y, cub3d->colours.floor_colour);
			y ++;
		}
		x ++;
	}
}
