/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:10:02 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/22 12:33:36 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	mouse_move(int x, int y, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	(void)y;
	if (cub3d->player.mouse_press == true)
	{
		if (x < cub3d->win_width / 2)
			rotate_to_left(&cub3d->player);
		else if (x > cub3d->win_width / 2)
			rotate_to_right(&cub3d->player);
		mlx_mouse_move(cub3d->mlx, cub3d->mlx_win, cub3d->win_width / 2,
			cub3d->win_height / 2);
	}
	return (0);
}

int	mouse_press(int keycode, int x, int y, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	(void)x;
	(void)y;
	if (keycode == LEFT_CLICK)
	{
		if (cub3d->player.mouse_press == true)
		{
			cub3d->player.mouse_press = false;
			printf("mouse rotation is OFF\n");
			mlx_mouse_show(cub3d->mlx, cub3d->mlx_win);
		}
		else
		{
			cub3d->player.mouse_press = true;
			printf("mouse rotation is ON\n");
		}
	}
	return (0);
}
