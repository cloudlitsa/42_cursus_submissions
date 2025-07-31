/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:05:10 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/23 21:54:19 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

static void	change_background(t_cub3d *cub3d)
{
	if (cub3d->draw_background_with_txtr == true)
		cub3d->draw_background_with_txtr = false;
	else
		cub3d->draw_background_with_txtr = true;
}

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
	else if (keycode == KEY_F)
		trigger_door_action(cub3d);
	else if (keycode == KEY_C)
		change_background(cub3d);
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
