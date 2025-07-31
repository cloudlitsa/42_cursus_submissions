/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:59:17 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/17 15:01:08 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	destroy_images(t_cub3d *cub3d)
{
	int		i;
	t_img	*img;

	i = 0;
	while (i < TXTRS_NBR)
	{
		img = &cub3d->txtrs[i].img;
		if (img->img_ptr)
		{
			mlx_destroy_image(cub3d->mlx, img->img_ptr);
			img->img_ptr = NULL;
		}
		i++;
	}
	if (cub3d->frame_buf.img_ptr)
	{
		mlx_destroy_image(cub3d->mlx, cub3d->frame_buf.img_ptr);
		cub3d->frame_buf.img_ptr = NULL;
	}
}

void	free_txtr_paths(t_cub3d *cub3d)
{
	int		i;

	i = 0;
	while (i < TXTRS_NBR)
	{
		if (cub3d->txtrs[i].txtr_path)
		{
			free(cub3d->txtrs[i].txtr_path);
			cub3d->txtrs[i].txtr_path = NULL;
		}
		i++;
	}
}

int	game_end(t_cub3d *cub3d)
{
	free_cub3d_data(cub3d);
	exit (EXIT_SUCCESS);
}

int	game_error(char *err_msg, t_cub3d *cub3d)
{
	gnl_cleanup_all();
	free_cub3d_data(cub3d);
	printf(R "Error\n%s\n" RESET, err_msg);
	exit(EXIT_FAILURE);
}
