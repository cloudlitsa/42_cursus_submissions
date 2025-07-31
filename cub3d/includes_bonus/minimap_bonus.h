/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:57:00 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/22 10:34:10 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

# include "cub3d_struct_bonus.h"

# define MINIMAP_WALLS_COLOUR 0xFFFFFF
# define MINIMAP_DOORS_COLOUR 0x189B05
# define MINIMAP_PLAYER_COLOUR 0x0000FF
# define MINIMAP_RAY_COLOUR 0xFFF380
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
# define MINIMAP_TILE_SIZE 5
# define MINIMAP_PLAYER_SIZE 3

void	draw_minimap(t_cub3d *cub3d);
void	draw_minimap_ray(t_cub3d *cub3d, t_ray *ray);
int		can_walk(t_cub3d *cub3d, double x, double y);

#endif
