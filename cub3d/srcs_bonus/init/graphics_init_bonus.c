/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:50:29 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/24 09:14:12 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

void	load_textures_to_graphics(t_cub3d *cub3d)
{
	cub3d->txtrs[TX_NORTH].txtr_path = ft_strdup(cub3d->textures.north);
	cub3d->txtrs[TX_SOUTH].txtr_path = ft_strdup(cub3d->textures.south);
	cub3d->txtrs[TX_WEST].txtr_path = ft_strdup(cub3d->textures.west);
	cub3d->txtrs[TX_EAST].txtr_path = ft_strdup(cub3d->textures.east);
	cub3d->txtrs[TX_FLOOR].txtr_path = ft_strdup(FLOOR_TXTR);
	cub3d->txtrs[TX_CEILING].txtr_path = ft_strdup(CEILING_TXTR);
	cub3d->txtrs[TX_DOOR].txtr_path = ft_strdup(DOOR_TXTR);
}

static void	create_frame_buffer(t_cub3d *cub3d, t_img *buf)
{
	buf->img_ptr = mlx_new_image(cub3d->mlx,
			cub3d->win_width, cub3d->win_height);
	if (!buf->img_ptr)
		game_error("Failed to create frame buffer image", cub3d);
	buf->addr = mlx_get_data_addr(buf->img_ptr, &buf->bpp,
			&buf->line_len, &buf->endian);
	if (!buf->addr)
		game_error("Failed to get frame buffer address", cub3d);
}

void	load_all_textures(t_cub3d *cub3d, t_txtr *txtrs)
{
	int		i;
	t_img	*img;

	i = 0;
	while (i < TXTRS_NBR)
	{
		if (!txtrs[i].txtr_path)
			game_error("Missing texture path.\n", cub3d);
		img = &txtrs[i].img;
		img->img_ptr = mlx_xpm_file_to_image(cub3d->mlx, txtrs[i].txtr_path,
				&txtrs[i].width, &txtrs[i].height);
		if (!img->img_ptr)
		{
			printf("Loading texture: %s\n", txtrs[i].txtr_path);
			game_error("Img_ptr. Problems with malloc.\n", cub3d);
		}
		img->addr = mlx_get_data_addr(img->img_ptr,
				&img->bpp, &img->line_len, &img->endian);
		if (!img->addr)
			game_error("Img_addr. Problems with malloc.\n", cub3d);
		i++;
	}
}

int	graphics_init(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		game_error("Mlx ptr. Problems with malloc.\n", cub3d);
	cub3d->mlx_win = mlx_new_window(cub3d->mlx, cub3d->win_width,
			cub3d->win_height, "Cub3D");
	if (!cub3d->mlx_win)
		game_error("Window. Problems with malloc.\n", cub3d);
	load_textures_to_graphics(cub3d);
	create_frame_buffer(cub3d, &cub3d->frame_buf);
	load_all_textures(cub3d, cub3d->txtrs);
	return (0);
}
