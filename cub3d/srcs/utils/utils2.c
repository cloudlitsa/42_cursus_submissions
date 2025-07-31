/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:29:05 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/21 16:37:16 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_texture(char **texture)
{
	if (!texture || !*texture)
		return ;
	free(*texture);
	*texture = NULL;
}

void	free_cub3d_data(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	gnl_cleanup_all();
	destroy_images(cub3d);
	free_txtr_paths(cub3d);
	if (cub3d->mlx_win)
	{
		mlx_destroy_window(cub3d->mlx, cub3d->mlx_win);
		cub3d->mlx_win = NULL;
	}
	if (cub3d->mlx)
	{
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
		cub3d->mlx = NULL;
	}
	free_texture(&cub3d->textures.north);
	free_texture(&cub3d->textures.south);
	free_texture(&cub3d->textures.west);
	free_texture(&cub3d->textures.east);
	if (cub3d->map.grid)
	{
		free_string_array(cub3d->map.grid);
		cub3d->map.grid = NULL;
	}
}
