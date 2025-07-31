/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:10:16 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/18 16:52:47 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
	{
		printf("Usage: %s <maps/map.cub>\n", argv[0]);
		return (1);
	}
	if (!validate_filename(argv[1]))
		return (1);
	init_cub3d(&cub3d);
	parse_scene_description_file(argv[1], &cub3d);
	graphics_init(&cub3d);
	start_game(&cub3d);
	return (0);
}
