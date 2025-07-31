/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:05:10 by mosokina          #+#    #+#             */
/*   Updated: 2025/06/20 18:41:15 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	key_press(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		cub3d->player.move_forward = true;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		cub3d->player.move_backward = true;
	else if (keycode == KEY_A)
		cub3d->player.strafe_left = true;
	else if (keycode == KEY_D)
		cub3d->player.strafe_right = true;
	else if (keycode == KEY_Q || keycode == KEY_LEFT)
		cub3d->player.rotate_left = true;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		cub3d->player.rotate_right = true;
	else if (keycode == KEY_ESC)
		game_end(cub3d);
	return (0);
}

int	key_release(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		cub3d->player.move_forward = false;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		cub3d->player.move_backward = false;
	else if (keycode == KEY_A)
		cub3d->player.strafe_left = false;
	else if (keycode == KEY_D)
		cub3d->player.strafe_right = false;
	else if (keycode == KEY_Q || keycode == KEY_LEFT)
		cub3d->player.rotate_left = false;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		cub3d->player.rotate_right = false;
	return (0);
}
