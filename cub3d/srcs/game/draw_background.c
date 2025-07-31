/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:48:05 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/14 11:22:04 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
