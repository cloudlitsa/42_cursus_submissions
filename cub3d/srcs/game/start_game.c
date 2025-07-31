/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:50:19 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/09 11:29:59 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	setup_event_hooks(t_cub3d *cub3d)
{
	mlx_hook(cub3d->mlx_win, X_EVENT_EXIT, 0, &game_end, cub3d);
	mlx_hook(cub3d->mlx_win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, cub3d);
	mlx_hook(cub3d->mlx_win, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, cub3d);
	mlx_hook(cub3d->mlx_win, X_EVENT_MOUSE_PRESS, 1L << 2, &mouse_press, cub3d);
	mlx_hook(cub3d->mlx_win, X_EVENT_MOUSE_MOVE, 1L << 6, &mouse_move, cub3d);
}

int	start_game(t_cub3d *cub3d)
{
	setup_event_hooks(cub3d);
	mlx_loop_hook(cub3d->mlx, &render_new_frame, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}
