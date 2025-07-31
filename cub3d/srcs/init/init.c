/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:29:22 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/24 13:02:36 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	init_colours(t_colours *colours)
{
	colours->floor_colour = UNSET_FLAG;
	colours->ceiling_colour = UNSET_FLAG;
}

static void	init_window(t_cub3d *cub3d)
{
	cub3d->mlx_win = NULL;
	cub3d->win_width = DEFAULT_WIDTH;
	cub3d->win_height = DEFAULT_HEIGHT;
	cub3d->frame_buf.img_ptr = NULL;
	cub3d->frame_buf.addr = NULL;
}

static void	init_map(t_cub3d *cub3d)
{
	cub3d->map.grid = NULL;
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	cub3d->map.player_orientation = '\0';
}

void	init_cub3d(t_cub3d *cub3d)
{
	cub3d->mlx = NULL;
	init_window(cub3d);
	ft_bzero(&cub3d->ray, sizeof(t_ray));
	ft_bzero(&cub3d->player, sizeof(t_player));
	ft_bzero(cub3d->txtrs, sizeof(t_txtr) * TXTRS_NBR);
	cub3d->textures.north = NULL;
	cub3d->textures.south = NULL;
	cub3d->textures.west = NULL;
	cub3d->textures.east = NULL;
	init_colours(&cub3d->colours);
	init_map(cub3d);
	cub3d->is_map_valid = false;
	cub3d->is_textures_loaded = false;
	cub3d->is_colours_set = false;
	cub3d->error = false;
	cub3d->map_started = false;
	cub3d->empty_line = false;
}
