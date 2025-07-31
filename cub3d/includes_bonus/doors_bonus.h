/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:00:47 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/22 10:38:33 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_BONUS_H
# define DOORS_BONUS_H

# include "cub3d_struct_bonus.h"

# define DOOR_CLOSED 0
# define DOOR_OPENED 100
# define DOOR_MAX_OPEN_OFFSET 0.5
# define DOOR_DURATION 0.5f

int		find_and_store_doors(t_cub3d *cub3d, const char *line);
void	restore_doors_to_map(t_cub3d *cub3d);
void	trigger_door_action(t_cub3d *cub3d);
void	animate_door(t_cub3d *cub3d, double delta_time);
t_door	*get_door_at_pos(t_cub3d *cub3d, int x, int y);
void	process_animated_door_hit(t_ray *ray, t_cub3d *cub3d, t_door *door);

#endif