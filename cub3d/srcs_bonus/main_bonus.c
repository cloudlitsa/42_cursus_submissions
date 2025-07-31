/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:38:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/23 20:21:24 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3D_bonus.h"

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
	{
		printf("Usage: %s <maps/map.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (!validate_filename(argv[1]))
		return (EXIT_FAILURE);
	init_cub3d(&cub3d);
	parse_scene_description_file(argv[1], &cub3d);
	graphics_init(&cub3d);
	start_game(&cub3d);
	return (0);
}
