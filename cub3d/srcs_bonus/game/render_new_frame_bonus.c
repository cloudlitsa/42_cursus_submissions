/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_new_frame_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:50:23 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/23 21:28:39 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

/*put a single pixel at position (x, y) 
in the frame buffer with a specific color.
*/

void	put_pixel_to_frame(t_cub3d *cub3d, int x, int y, int colour)
{
	char	*pixel;

	if (y < 0 || y >= cub3d->win_height || x < 0 || x >= cub3d->win_width)
		return ;
	pixel = cub3d->frame_buf.addr + (y * cub3d->frame_buf.line_len
			+ x * (cub3d->frame_buf.bpp / 8));
	*(int *)pixel = colour;
}

int	darken_colour(int color, double distance)
{
	double	shade;
	int		r;
	int		g;
	int		b;

	shade = 1.0 / (1.0 + distance * 0.1);
	if (shade < 0.2)
		shade = 0.2;
	r = ((color >> 16) & 0xFF) * shade;
	g = ((color >> 8) & 0xFF) * shade;
	b = (color & 0xFF) * shade;
	return ((r << 16) | (g << 8) | b);
}

int	get_colour_from_texture(t_txtr txtr, t_vec2i txtr_pos)
{
	char	*pixel;

	if (txtr_pos.x < 0 || txtr_pos.x >= txtr.width || txtr_pos.y < 0
		|| txtr_pos.y >= txtr.height)
		return (0);
	pixel = txtr.img.addr + (txtr_pos.y * txtr.img.line_len
			+ txtr_pos.x * (txtr.img.bpp / 8));
	return (*(int *)pixel);
}

int	render_new_frame(t_cub3d *cub3d)
{
	double	current_time;
	double	delta_time;

	current_time = get_time_seconds();
	delta_time = current_time - cub3d->last_frame_time;
	cub3d->last_frame_time = current_time;
	if (cub3d->draw_background_with_txtr == true)
		draw_background_with_txtr(cub3d);
	else
		draw_background_with_colour(cub3d);
	handle_input(cub3d, &cub3d->player);
	if (cub3d->animated_door != NULL)
		animate_door(cub3d, delta_time);
	raycasting(cub3d);
	draw_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win,
		cub3d->frame_buf.img_ptr, 0, 0);
	return (0);
}
